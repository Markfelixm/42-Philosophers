/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/25 18:39:57 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

bool	print_activity(t_seat *seat, t_activity activity)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static const char		*message[] = {
		"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};
	static const char		*colors[] = {
		"\033[0;31m", "\033[0;32m", "\033[0;33m",
		"\033[0;34m", "\033[0;35m", "\033[0;36m"};
	const long				ts = time_since_timestamp(&(seat->table->init_ts));

	if (ts == -1)
		return (false);
	if (has_anyone_died(seat))
		return (true);
	if (pthread_mutex_lock(&print_mutex))
		return (false);
	printf("%ld %s%d\033[0m %s\n",
		ts,
		colors[seat->pos % 6], seat->pos + 1,
		message[activity]);
	if (activity == DIED)
		set_died_state(seat);
	if (pthread_mutex_unlock(&print_mutex))
		return (false);
	return (true);
}
