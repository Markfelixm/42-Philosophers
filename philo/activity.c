/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:03:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/19 22:07:45 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

bool	has_died(t_table *table, int seat)
{
	const long	time = time_since_timestamp(&(table->seats[seat].meal_ts));

	if (time > table->time_to_die || time == -1)
		return (true);
	return (false);
}

void	lives(t_seat *seat)
{
	if (seat->pos % 2)
		if (usleep(seat->table->time_to_eat))
			seat->error = true;
	while (42)
	{
		if (!eats(seat))
			seat->error = true;
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
	if (seat->meals_eaten < seat->table->num_of_meals
		|| seat->table->num_of_meals == -1)
	{
		if (!lock_forks(seat))
			return (false);
		if (!print_activity(seat, EATING))
			return (false);
		if (gettimeofday(&(seat->meal_ts), NULL))
			return (false);
		seat->meals_eaten++;
		if (usleep(seat->table->time_to_eat * 1000))
			return (false);
		if (!unlock_forks(seat->table, seat->pos))
			return (false);
	}
	return (true);
}

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
