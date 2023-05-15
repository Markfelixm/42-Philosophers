/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/15 20:51:20 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments.\n", 30));
	if (init_table(ac, av, &table) == false)
		return (write(2, "Table initialization failed.\n", 30));
	monitor_philosophers(&table);
}

bool	monitor_philosophers(t_table *table)
{
	int		philos_done_eating;
	int		seat;

	philos_done_eating = 0;
	while (42)
	{
		seat = 0;
		while (seat < table->num_of_seats)
		{
			if (has_died(&table, seat))
				return (print_activity(&table, seat, DIED));
			if (table->seats[seat].meals_eaten == table->num_of_meals)
				philos_done_eating++;
			if (philos_done_eating == table->num_of_seats)
				return (true);
		}
	}
	return (false);
}
