/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/04 21:50:42 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <limits.h>

// static int	ft_strlen(const char *str)
// {
// 	int	len;

// 	len = 0;
// 	while (*(str++))
// 		len++;
// 	return (len);
// }

// static void	ft_putstr(const char *str)
// {
// 	write(1, str, ft_strlen(str));
// }

// static void	ft_putnum(long i)
// {
// 	const char	decimal[] = "0123456789";

// 	if (i == LONG_MIN)
// 		i = LONG_MAX;
// 	if (i < 0)
// 		i *= -1;
// 	if (i >= 10)
// 		ft_putnum(i / 10);
// 	write(1, &decimal[i % 10], 1);
// }

t_tri	print_activity(t_seat *seat, t_activity activity)
{
	long					ts;
	static const char		*message[] = {
		"has taken a fork\n", "is eating\n",
		"is sleeping\n", "is thinking\n", "died\n"};
	static const char		*colors[] = {
		" \033[0;31m", " \033[0;32m", " \033[0;33m",
		" \033[0;34m", " \033[0;35m", " \033[0;36m"};

	if (activity != TAKEN_FORK && has_anyone_died(seat->table))
		return (TRUE);
	if (pthread_mutex_lock(&(seat->table->print)))
		return (ERROR);
	ts = time_since_timestamp(&(seat->table->init_ts));
	if (ts == -1)
		return (ERROR);
	// ft_putnum(ts);
	// write(1, colors[seat->pos % 6], 9);
	// ft_putnum(seat->pos + 1);
	// write(1, "\033[0m ", 6);
	// ft_putstr(message[activity]);
	(void) colors;
	printf("%ld %d %s", ts, seat->pos + 1, message[activity]);
	if (pthread_mutex_unlock(&(seat->table->print)))
		return (ERROR);
	return (FALSE);
}
