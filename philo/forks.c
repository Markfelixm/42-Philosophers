/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:50:13 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 19:10:27 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_forks(t_seat *seat)
{
	const int	pos = seat->pos;
	t_seat		*all_seats;

	all_seats = seat->table->seats;
	seat->left_fork = &(seat->fork);
	if (pos == seat->table->num_of_seats - 1)
		seat->right_fork = &(all_seats[0].fork);
	else
		seat->right_fork = &(all_seats[pos + 1].fork);
}

t_tri	lock_forks(t_seat *seat)
{
	t_tri	state;

	if (pthread_mutex_lock(seat->left_fork))
		return (ERROR);
	state = print_activity(seat, TAKEN_FORK);
	if (state)
	{
		if (pthread_mutex_unlock(seat->left_fork))
			return (ERROR);
		return (state);
	}
	if (pthread_mutex_lock(seat->right_fork))
		return (ERROR);
	state = print_activity(seat, TAKEN_FORK);
	if (state)
	{
		if (unlock_forks(seat))
			return (ERROR);
		return (state);
	}
	return (FALSE);
}

t_tri	unlock_forks(t_seat *seat)
{
	if (pthread_mutex_unlock(seat->right_fork))
		return (ERROR);
	if (pthread_mutex_unlock(seat->left_fork))
		return (ERROR);
	return (FALSE);
}
