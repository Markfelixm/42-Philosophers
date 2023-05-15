/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:02:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/15 20:59:34 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <sys/time.h>

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
	if (!gettimeofday(&(table->init_timestamp), NULL))
		return (false);
	if (!init_seats(table))
		return (false);
	return (true);
}

bool	init_seats(t_table *table)
{
	int	seat;

	seat = 0;
	while (seat < table->num_of_seats)
	{
		if (!pthread_mutex_init(&(table->seats[seat].fork), NULL))
			return (false);
		if (!pthread_create(&(table->seats[seat].philo), NULL, live, NULL))
			return (false);
		seat++;
	}
	return (true);
}

bool	destroy_seats(t_table *table)
{
	int	seat;

	seat = 0;
	while (seat < table->num_of_seats)
	{
		if (!pthread_mutex_destroy(&(table->seats[seat].fork)))
			return (false);
		if (!pthread_detach(&(table->seats[seat].philo)))
			return (false);
		seat++;
	}
	return (true);
}
