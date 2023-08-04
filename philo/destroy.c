/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:33:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/04 22:36:19 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_tri	join_threads(t_table *table, int until)
{
	void	*exit_code;
	int		pos;

	exit_code = malloc(sizeof(void *));
	if (!exit_code)
		return (ERROR);
	pos = -1;
	while (++pos <= until)
	{
		if (pthread_join(table->seats[pos].philo, exit_code))
			// || (*((t_tri *) exit_code) == ERROR))
		{
			printf("[UNIFY] %d failed to join\n", pos + 1);
			free(exit_code);
			return (ERROR);
		}
		if (*((t_tri *) exit_code) == ERROR)
		{
			printf("[UNIFY] %d exit code was error\n", pos + 1);
		}
	}
	free(exit_code);
	return (FALSE);
}

t_tri	destroy_seats(t_seat *seats, int until)
{
	int	pos;

	pos = -1;
	while (++pos <= until)
	{
		if (pthread_mutex_destroy(&(seats[pos].fork)))
		{
			printf("[UNIFY] %d failed to destroy fork\n", pos + 1);
			return (ERROR);
		}
		if (pthread_mutex_destroy(&(seats[pos].meal_ts_mutex)))
		{
			printf("[UNIFY] %d failed to destroy meal_ts_mutex\n", pos + 1);
			return (ERROR);
		}
	}
	return (FALSE);
}

t_tri	destroy_table(t_table *table)
{
	if (pthread_mutex_destroy(&(table->death_mutex))
		|| pthread_mutex_destroy(&(table->gate))
		|| pthread_mutex_destroy(&(table->print)))
		return (ERROR);
	return (FALSE);
}
