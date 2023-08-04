/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:03:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/04 22:48:47 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

t_tri	lives(t_seat *seat)
{
	t_tri	state;

	if (pthread_mutex_lock(&(seat->table->gate))
		|| pthread_mutex_unlock(&(seat->table->gate))
		|| pthread_mutex_lock(&(seat->meal_ts_mutex))
		|| gettimeofday(&(seat->meal_ts), NULL)
		|| pthread_mutex_unlock(&(seat->meal_ts_mutex)))
		return (ERROR);
	state = is_lonely_philo(seat);
	if (state)
		return (state);
	if (seat->pos % 2)
		if (ft_usleep(seat->table->time_to_die * 250))
			return (ERROR);
	while (42)
	{
		state = has_died(seat);
		if (state)
			return (state);
		if (eats(seat) == ERROR)
			return (ERROR);
		state = is_done_eating(seat);
		if (state)
			return (state);
		state = print_activity(seat, SLEEPING);
		if (state)
			return (state);
		if (ft_usleep(seat->table->time_to_sleep * 1000))
			return (ERROR);
		state = print_activity(seat, THINKING);
		if (state)
			return (state);
	}
	return (ERROR);
}

t_tri	eats(t_seat *seat)
{
	t_tri	state;

	state = lock_forks(seat);
	if (state)
		return (state);
	seat->meals_eaten++;
	state = print_activity(seat, EATING);
	if (state)
		return (state);
	if (pthread_mutex_lock(&(seat->meal_ts_mutex))
		|| gettimeofday(&(seat->meal_ts), NULL)
		|| pthread_mutex_unlock(&(seat->meal_ts_mutex)))
		return (ERROR);
	if (ft_usleep(seat->table->time_to_eat * 1000))
		return (ERROR);
	if (unlock_forks(seat) == ERROR)
		return (ERROR);
	return (TRUE);
}

t_tri	is_done_eating(t_seat *seat)
{
	t_tri	is_done;

	if (seat->table->num_of_meals != -1
		&& seat->meals_eaten >= seat->table->num_of_meals)
		is_done = TRUE;
	else
		is_done = FALSE;
	return (is_done);
}

t_tri	is_lonely_philo(t_seat *seat)
{
	t_tri	state;

	if (seat->table->num_of_seats != 1)
		return (FALSE);
	if (pthread_mutex_lock(seat->left_fork))
		return (ERROR);
	state = print_activity(seat, TAKEN_FORK);
	if (state)
	{
		if (pthread_mutex_unlock(seat->left_fork))
			return (ERROR);
		return (state);
	}
	if (ft_usleep(seat->table->time_to_die * 1000))
	{
		pthread_mutex_unlock(seat->left_fork);
		return (ERROR);
	}
	state = print_activity(seat, DIED);
	if (pthread_mutex_unlock(seat->left_fork) || state == ERROR)
		return (ERROR);
	return (TRUE);
}
