/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:50:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/24 14:52:04 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	lock_forks(t_seat *seat)
{
	if (pthread_mutex_lock(&(seat->fork)))
		return (false);
	if (!print_activity(seat, TAKING_FORK))
		return (false);
	if (seat->pos == seat->table->num_of_seats - 1)
	{
		if (pthread_mutex_lock(&(seat->table->seats[0].fork)))
			return (false);
	}
	else
	{
		if (pthread_mutex_lock(&(seat->table->seats[seat->pos + 1].fork)))
			return (false);
	}
	if (!print_activity(seat, TAKING_FORK))
		return (false);
	return (true);
}

bool	unlock_forks(t_table *table, int pos)
{
	if (pos == table->num_of_seats - 1)
	{
		if (pthread_mutex_unlock(&(table->seats[0].fork)))
			return (false);
	}
	else
	{
		if (pthread_mutex_unlock(&(table->seats[pos + 1].fork)))
			return (false);
	}
	if (pthread_mutex_unlock(&(table->seats[pos].fork)))
		return (false);
	return (true);
}

bool	get_died_state(t_seat *seat)
{
	bool	someone_died;

	if (pthread_mutex_lock(&(seat->table->died_mutex)))
		return (seat->error = true, true);
	someone_died = seat->table->has_anyone_died;
	if (pthread_mutex_unlock(&(seat->table->died_mutex)))
		return (seat->error = true, true);
	return (someone_died);
}

void	set_died_state(t_seat *seat)
{
	if (pthread_mutex_lock(&(seat->table->died_mutex)))
	{
		seat->error = true;
		return ;
	}
	seat->table->has_anyone_died = true;
	if (pthread_mutex_unlock(&(seat->table->died_mutex)))
		seat->error = true;
}

bool	has_anyone_died(t_seat *seat)
{
	bool	death_occured;

	if (pthread_mutex_lock(&(seat->table->died_mutex)))
		return (false);
	death_occured = seat->table->has_anyone_died;
	if (pthread_mutex_unlock(&(seat->table->died_mutex)))
		return (false);
	return (death_occured);
}
