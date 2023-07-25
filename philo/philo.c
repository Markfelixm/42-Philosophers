/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/25 18:40:07 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments.\n", 30));
	if (!init_table(&table, ac, av))
		return (write(2, "Table initialization failed.\n", 30));
	if (!monitor_philosophers(&table))
		return (write(2, "Error during routine.\n", 23));
	if (!destroy_all_humans(&table))
		return (write(2, "Could not destroy all humans :(\n", 33));
}

bool	monitor_philosophers(t_table *table)
{
	static int	philos_done_eating = 0;
	int			pos;

	while (42)
	{
		pos = -1;
		while (++pos < table->num_of_seats)
		{
			if (has_died(table, pos))
				return (print_activity(&(table->seats[pos]), DIED));
			if (table->seats[pos].error
				|| pthread_mutex_lock(&(table->seats[pos].meals_mutex)))
				return (false);
			if (table->seats[pos].meals_eaten == table->num_of_meals)
			{
				table->seats[pos].meals_eaten++;
				philos_done_eating++;
			}
			if (pthread_mutex_unlock(&(table->seats[pos].meals_mutex)))
				return (false);
			if (philos_done_eating == table->num_of_seats)
				return (true);
		}
	}
	return (false);
}
