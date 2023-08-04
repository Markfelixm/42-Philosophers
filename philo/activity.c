/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:03:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/31 18:40:01 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	lives(t_seat *seat)
{
	if (pthread_mutex_lock(&(seat->table->gate))
		|| pthread_mutex_unlock(&(seat->table->gate)))
		seat->error = true;
	if (seat->pos % 2)
		if (usleep((seat->table->time_to_die * 1000) / 4))
			seat->error = true;
	while (42)
	{
		if (is_lonely_philo(seat)
			|| is_done_eating(seat)
			|| has_anyone_died(seat))
			return ;
		if (!eats(seat))
			seat->error = true;
		if (is_done_eating(seat) || has_anyone_died(seat))
			return ;
		if (!print_activity(seat, SLEEPING))
			seat->error = true;
		if (usleep(seat->table->time_to_sleep * 1000))
			seat->error = true;
		if (!print_activity(seat, THINKING))
			seat->error = true;
	}
}

bool	eats(t_seat *seat)
{
	if (!is_done_eating(seat))
	{
		if (!lock_forks(seat))
			return (false);
		if (gettimeofday(&(seat->meal_ts), NULL))
			return (false);
		if (!print_activity(seat, EATING))
			return (false);
		if (pthread_mutex_lock(&(seat->meals_mutex)))
			return (false);
		seat->meals_eaten++;
		if (pthread_mutex_unlock(&(seat->meals_mutex)))
			return (false);
		if (usleep(seat->table->time_to_eat * 1000))
			return (false);
		if (!unlock_forks(seat->table, seat->pos))
			return (false);
	}
	return (true);
}

bool	is_done_eating(t_seat *seat)
{
	bool	is_done;

	if (pthread_mutex_lock(&(seat->meals_mutex)))
		return (seat->error = true, true);
	is_done = (seat->table->num_of_meals != -1
			&& seat->meals_eaten >= seat->table->num_of_meals);
	if (pthread_mutex_unlock(&(seat->meals_mutex)))
		return (seat->error = true, true);
	return (is_done);
}

bool	has_died(t_table *table, int seat)
{
	const long	time = time_since_timestamp(&(table->seats[seat].meal_ts));

	if (time > table->time_to_die)
		return (true);
	if (time == -1)
	{
		table->seats[seat].error = true;
		return (true);
	}
	return (false);
}

bool	is_lonely_philo(t_seat *seat)
{
	if (seat->table->num_of_seats != 1)
		return (false);
	if (pthread_mutex_lock(&(seat->fork)))
		return (seat->error = true, true);
	if (!print_activity(seat, TAKING_FORK))
		return (seat->error = true, true);
	if (usleep(seat->table->time_to_die * 1000))
		return (seat->error = true, true);
	if (pthread_mutex_unlock(&(seat->fork)))
		return (seat->error = true, true);
	return (true);
}
