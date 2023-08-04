/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:05 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/04 22:54:27 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>


int	main(int ac, char **av)
{
	t_table	table;
	t_tri	state;

	// check leaks
	// repo probably has old files abnd .vscode
	if (ac < 5 || ac > 6)
		return (write(2, "Invalid number of arguments.\n", 30));
	state = init_table(&table, ac, av);
	if (state == TRUE)
		return (write(2, "Invalid input.\n", 16));
	else if (state == ERROR)
		return (write(2, "Table initialization failed.\n", 30));
	if (join_threads(&table, table.num_of_seats - 1))
		return (write(2, "Could not join threads\n", 24));
	if (destroy_seats(table.seats, table.num_of_seats - 1))
		return (write(2, "Could not destroy seats\n", 25));
	if (destroy_table(&table))
		return (write(2, "Could not destroy table\n", 25));
}
