/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:04:06 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/19 20:18:56 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
