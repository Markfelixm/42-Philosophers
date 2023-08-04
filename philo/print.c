/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/31 18:38:14 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>
#include <unistd.h>

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}

static void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

static void	ft_putnum(long i)
{
	const char	decimal[] = "0123456789";

	if (i == LONG_MIN)
		i = LONG_MAX;
	if (i < 0)
		i *= -1;
	if (i > 10)
		ft_putnum(i / 10);
	write(1, &decimal[i % 10], 1);
}

bool	print_activity(t_seat *seat, t_activity activity)
{
	static const char		*message[] = {
		"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};
	long					ts;

	if (pthread_mutex_lock(&(seat->table->print_mutex)))
		return (false);
	ts = time_since_timestamp(&(seat->table->init_ts));
	if (ts == -1)
		return (false);
	ft_putnum(ts);
	write(1, " ", 1);
	ft_putnum(seat->pos + 1);
	write(1, " ", 1);
	ft_putstr(message[activity]);
	write(1, "\n", 1);
	if (pthread_mutex_unlock(&(seat->table->print_mutex)))
		return (false);
	return (true);
}
