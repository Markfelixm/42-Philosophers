/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:02:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/19 20:27:29 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

bool	init_table(int ac, char **av, t_table *table)
{
	memset(table, 0, sizeof(t_table));
	table->num_of_seats = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->num_of_meals = -1;
	if (ac == 6)
		table->num_of_meals = ft_atoi(av[5]);
	if (gettimeofday(&(table->init_ts), NULL))
		return (false);
	if (!init_seats(table))
		return (false);
	return (true);
}

bool	init_seats(t_table *table)
{
	int	pos;

	pos = 0;
	while (pos < table->num_of_seats)
	{
		if (pthread_mutex_init(&(table->seats[pos].fork), NULL))
			return (false);
		table->seats[pos].pos = pos;
		table->seats[pos].error = false;
		table->seats[pos].table = table;
		table->seats[pos].meal_ts = table->init_ts;
		if (pthread_create(&(table->seats[pos].philo), NULL,
				(void *(*)(void *)) lives, &(table->seats[pos])))
			return (false);
		pos++;
	}
	return (true);
}

bool	destroy_all_humans(t_table *table)
{
	int	pos;

	pos = -1;
	while (++pos < table->num_of_seats)
		if (pthread_mutex_destroy(&(table->seats[pos].fork)))
			return (false);
	return (true);
}
