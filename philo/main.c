/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/06 15:43:22 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;
	t_tri	state;

	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments.\n", 30));
	state = init_table(&table, ac, av);
	if (state == TRUE)
		return (write(2, "Invalid input.\n", 16));
	else if (state == ERROR)
		return (write(2, "Table initialization failed.\n", 30));
	if (monitor_philosophers(&table) == ERROR)
		return (write(2, "Monitoring errored.\n", 21));
	state = join_threads(&table, table.num_of_seats - 1);
	if (state == TRUE)
		return (write(2, "Routine exited with error.\n", 28));
	else if (state == ERROR)
		return (write(2, "Could not join threads.\n", 25));
	if (destroy_seats(table.seats, table.num_of_seats - 1))
		return (write(2, "Could not destroy seats.\n", 26));
	if (destroy_table(&table))
		return (write(2, "Could not destroy table.\n", 26));
}

t_tri	monitor_philosophers(t_table *table)
{
	t_tri	state;
	int		pos;
	int		philos_done_eating;

	philos_done_eating = 0;
	while (42)
	{
		if (ft_usleep(table->num_of_seats * 10))
			return (ERROR);
		pos = -1;
		while (++pos < table->num_of_seats)
		{
			state = is_done_eating(&(table->seats[pos]));
			if (state == TRUE)
				philos_done_eating++;
			else if (state == ERROR)
				return (ERROR);
			if (philos_done_eating >= table->num_of_seats)
				return (TRUE);
			state = has_died(&(table->seats[pos]));
			if (state)
				return (state);
		}
	}
	return (ERROR);
}
