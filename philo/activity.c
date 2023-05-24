/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:03:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/24 14:51:49 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	lives(t_seat *seat)
{
	if (seat->pos % 2)
		if (usleep(seat->table->time_to_eat))
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

bool	is_done_eating(t_seat *seat)
{
	return (seat->table->num_of_meals != -1
		&& seat->meals_eaten >= seat->table->num_of_meals);
}

bool	has_died(t_table *table, int seat)
{
	const long	time = time_since_timestamp(&(table->seats[seat].meal_ts));

	if (time > table->time_to_die || time == -1)
		return (true);
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
