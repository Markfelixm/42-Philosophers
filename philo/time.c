/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:04:06 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/04 18:17:27 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

long	time_since_timestamp(struct timeval *ts)
{
	struct timeval	now;
	long			diff;

	if (gettimeofday(&now, NULL))
		return (-1);
	diff = now.tv_usec - ts->tv_usec;
	diff += 1000000 * (now.tv_sec - ts->tv_sec);
	diff /= 1000;
	return (diff);
}

long	ft_usleep(long us)
{
	return (usleep(us));
	// struct timeval	begin;
	// long			diff;

	// if (gettimeofday(&begin, NULL))
	// 	return (-1);
	// while (42)
	// {
	// 	diff = time_since_timestamp(&begin);
	// 	if (diff >= us)
	// 		return (0);
	// 	else if (diff == -1)
	// 		return (-1);
	// 	else
	// 		if (usleep(USLEEP_INTERVAL))
	// 			return (-1);
	// }
	// return (0);
}