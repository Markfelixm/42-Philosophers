/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:02:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 20:03:06 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <limits.h>

t_tri	valid_input(t_table *table, int ac, char **av)
{
	if (table->num_of_seats < 1 || table->num_of_seats > 200)
		return (FALSE);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (FALSE);
	if (ac == 6)
		if (ft_atoi(av[5]) <= 0)
			return (FALSE);
	return (TRUE);
}

t_tri	init_seats(t_table *table)
{
	int	pos;

	pos = -1;
	if (pthread_mutex_lock(&(table->gate)))
		return (ERROR);
	while (++pos < table->num_of_seats)
	{
		if (pthread_mutex_init(&(table->seats[pos].fork), NULL)
			|| pthread_mutex_init(&(table->seats[pos].meal_ts_mutex), NULL))
			return (ERROR);
		table->seats[pos].pos = pos;
		table->seats[pos].table = table;
		if (pthread_create(&(table->seats[pos].philo), NULL,
				(void *(*)(void *)) lives, &(table->seats[pos])))
			if (join_threads(table, pos) == ERROR)
				return (ERROR);
	}
	pos = -1;
	while (++pos < table->num_of_seats)
		assign_forks(&(table->seats[pos]));
	if (pthread_mutex_unlock(&(table->gate)))
		return (ERROR);
	return (TRUE);
}

t_tri	init_table(t_table *table, int ac, char **av)
{
	memset(table, 0, sizeof(t_table));
	if (pthread_mutex_init(&(table->death_mutex), NULL)
		|| pthread_mutex_init(&(table->gate), NULL)
		|| pthread_mutex_init(&(table->print), NULL))
		return (ERROR);
	table->death_occured = FALSE;
	table->num_of_seats = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->num_of_meals = -1;
	if (!valid_input(table, ac, av))
	{
		if (pthread_mutex_destroy(&(table->death_mutex))
			|| pthread_mutex_destroy(&(table->gate))
			|| pthread_mutex_destroy(&(table->print)))
			return (ERROR);
		return (TRUE);
	}
	if (ac == 6)
		table->num_of_meals = ft_atoi(av[5]);
	table->init_ts = get_current_ms();
	if (init_seats(table) == ERROR)
		return (ERROR);
	return (FALSE);
}
