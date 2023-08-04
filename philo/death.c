/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:59:03 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/04 20:59:02 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tri	set_died_state(t_table *table)
{
	if (pthread_mutex_lock(&(table->death_mutex)))
		return (ERROR);
	table->death_occured = TRUE;
	if (pthread_mutex_unlock(&(table->death_mutex)))
		return (ERROR);
	return (TRUE);
}

t_tri	has_anyone_died(t_table *table)
{
	t_tri	death_occured;

	if (pthread_mutex_lock(&(table->death_mutex)))
		return (ERROR);
	death_occured = table->death_occured;
	if (pthread_mutex_unlock(&(table->death_mutex)))
		return (ERROR);
	return (death_occured);
}

t_tri	has_died(t_seat *seat)
{
	long	time;
	t_tri	is_dead;
	t_tri	print_state;
	t_tri	set_state;

	is_dead = FALSE;
	if (pthread_mutex_lock(&(seat->meal_ts_mutex)))
		return (ERROR);
	time = time_since_timestamp(&(seat->meal_ts));
	if (has_anyone_died(seat->table) == FALSE && time > seat->table->time_to_die)
	{
		is_dead = TRUE;
		print_state = print_activity(seat, DIED);
		set_state = set_died_state(seat->table);
	}
	if (pthread_mutex_unlock(&(seat->meal_ts_mutex))
		|| time == -1 || print_state == ERROR || set_state == ERROR)
		return (ERROR);
	return (is_dead);
}