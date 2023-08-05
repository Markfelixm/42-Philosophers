/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:03:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 19:37:38 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_tri	lives(t_seat *seat)
{
	t_tri	state;

	state = init_routine(seat);
	if (state)
		return (state);
	while (42)
	{
		state = eats(seat);
		if (state)
			return (state);
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

t_tri	init_routine(t_seat *seat)
{
	t_tri	state;

	if (pthread_mutex_lock(&(seat->table->gate))
		|| pthread_mutex_unlock(&(seat->table->gate)))
		return (ERROR);
	if (pthread_mutex_lock(&(seat->meal_ts_mutex)))
		return (ERROR);
	seat->meal_ts = get_current_ms();
	if (pthread_mutex_unlock(&(seat->meal_ts_mutex)))
		return (ERROR);
	state = is_lonely_philo(seat);
	if (state)
		return (state);
	if (seat->pos % 2)
		if (ft_usleep(seat->table->time_to_eat * 500))
			return (ERROR);
	return (FALSE);
}

t_tri	eats(t_seat *seat)
{
	t_tri	state;

	state = lock_forks(seat);
	if (state)
		return (state);
	seat->meals_eaten++;
	if (pthread_mutex_lock(&(seat->meal_ts_mutex)))
		return (ERROR);
	seat->meal_ts = get_current_ms();
	if (pthread_mutex_unlock(&(seat->meal_ts_mutex)))
		return (ERROR);
	state = print_activity(seat, EATING);
	if (state)
	{
		if (unlock_forks(seat))
			return (ERROR);
		return (state);
	}
	if (ft_usleep(seat->table->time_to_eat * 1000)
		|| unlock_forks(seat))
		return (ERROR);
	return (FALSE);
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
	if (pthread_mutex_unlock(seat->left_fork))
		return (ERROR);
	return (TRUE);
}
