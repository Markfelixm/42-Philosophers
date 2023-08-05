/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:33:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 19:24:09 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tri	join_threads(t_table *table, int until)
{
	t_tri	state;
	void	*exit_code;
	int		pos;

	exit_code = malloc(sizeof(void *));
	if (!exit_code)
		return (ERROR);
	state = FALSE;
	pos = -1;
	while (++pos <= until)
	{
		if (pthread_join(table->seats[pos].philo, exit_code))
			state = ERROR;
		if (*((t_tri *) exit_code) == ERROR)
			state = TRUE;
	}
	free(exit_code);
	return (state);
}

t_tri	destroy_seats(t_seat *seats, int until)
{
	int	pos;

	pos = -1;
	while (++pos <= until)
	{
		if (pthread_mutex_destroy(&(seats[pos].fork))
			|| pthread_mutex_destroy(&(seats[pos].meal_ts_mutex)))
			return (ERROR);
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
