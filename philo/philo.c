/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/24 18:10:58 by marmulle         ###   ########.fr       */
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
	int		philos_done_eating;
	int		pos;

	philos_done_eating = 0;
	while (42)
	{
		pos = -1;
		while (++pos < table->num_of_seats)
		{
			if (table->seats[pos].error)
				return (false);
			if (has_died(table, pos))
				return (print_activity(&(table->seats[pos]), DIED));
			if (table->seats[pos].meals_eaten == table->num_of_meals)
			{
				table->seats[pos].meals_eaten++;
				philos_done_eating++;
			}
			if (philos_done_eating == table->num_of_seats)
				return (true);
			if (usleep(5000 / table->num_of_seats))
				return (false);
		}
	}
	return (false);
}
