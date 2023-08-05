/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:04:06 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 18:53:16 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ll	get_ms(struct timeval *ts)
{
	t_ll	out;

	out = ts->tv_usec / 1000LL;
	out += ts->tv_sec * 1000LL;
	return (out);
}

t_ll	get_current_ms(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL))
		return (-1);
	return (get_ms(&now));
}

t_ll	time_since_timestamp(t_ll ts)
{
	t_ll	out;

	out = get_current_ms() - ts;
	if (out < 0)
		out = -1;
	return (out);
}

int	ft_usleep(t_ll us)
{
	t_ll	start;

	start = get_current_ms();
	while (42)
	{
		if (time_since_timestamp(start) * 1000 >= us)
			return (0);
		if (usleep(USLEEP_INTERVAL))
			return (-1);
	}
	return (-1);
}
