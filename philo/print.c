/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 19:00:31 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tri	print_activity(t_seat *seat, t_activity activity)
{
	long long				ts;
	static const char		*message[] = {
		"has taken a fork\n", "is eating\n",
		"is sleeping\n", "is thinking\n", "\033[0;31mdied\033[0m\n"};
	static const char		*colors[] = {
		"\033[0;31m", "\033[0;32m", "\033[0;33m",
		"\033[0;34m", "\033[0;35m", "\033[0;36m"};

	if (has_anyone_died(seat->table))
		return (TRUE);
	if (pthread_mutex_lock(&(seat->table->print)))
		return (ERROR);
	ts = time_since_timestamp(seat->table->init_ts);
	if (ts == -1)
		return (ERROR);
	printf("%lld %s%d\033[0m %s",
		ts,
		colors[seat->pos % 6], seat->pos + 1,
		message[activity]);
	if (pthread_mutex_unlock(&(seat->table->print)))
		return (ERROR);
	return (FALSE);
}
