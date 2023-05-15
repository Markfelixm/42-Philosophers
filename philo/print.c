/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/15 20:51:29 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	print_activity(t_table *table, int seat, t_activity activity)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static const char		*message[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};
	const long				ts = time_since_timestamp(table->init_timestamp);

	if (ts == -1)
		return (false);
	if (pthread_mutex_lock(&print_mutex))
		return (false);
	printf("%ld %d %s\n",
		ts,
		seat,
		message[activity]);
	if (activity == DIED)
		return (true);
	if (!pthread_mutex_unlock(&print_mutex))
		return (false);
	return (true);
}

bool	lock_fork_and_print(t_table *table, int seat)
{
	if (!pthread_mutex_lock(&(table->seats[seat].fork)))
		return (false);
	print_activity(table, seat, TAKING_FORK);
	return (true);
}
