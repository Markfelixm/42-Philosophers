/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:03:18 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/15 20:53:06 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_died(t_table *table, int seat)
{
	const long	time = time_since_timestamp(table->seats[seat].meal_timestamp);

	if (time > table->time_to_die || time == -1)
		return (true);
	return (false);
}

bool	lives(t_table *table, int seat)
{
	while (42)
	{
		eats(table, seat);
		if (!print_activity(table, seat, SLEEPING))
			return (false);
		if (!usleep(table->time_to_sleep * 1000))
			return (false);
		if (!print_activity(table, seat, THINKING))
			return (false);
	}
	return (true);
}

bool	eats(t_table *table, int seat)
{
	if (table->seats[seat].meals_eaten < table->num_of_meals
		|| table->num_of_meals == -1)
	{
		if (!lock_forks(table, seat))
			return (false);
		if (!print_activity(table, seat, EATING))
			return (false);
		if (!gettimeofday(&(table->seats[seat].meal_timestamp), NULL))
			return (false);
		table->seats[seat].meals_eaten++;
		if (!usleep(table->time_to_eat * 1000))
			return (false);
		if (!unlock_forks(table, seat))
			return (false);
	}
	return (true);
}

bool	lock_forks(t_table *table, int seat)
{
	if (seat % 2 == 0)
	{
		if (!lock_fork_and_print(table, seat))
			return (false);
		if (seat == table->num_of_seats - 1)
			if (!lock_fork_and_print(table, 0))
				return (false);
		else
			if (!lock_fork_and_print(table, seat + 1))
				return (false);
	}
	else
	{
		if (seat == table->num_of_seats - 1)
			if (!lock_fork_and_print(table, 0))
				return (false);
		else
			if (!lock_fork_and_print(table, seat + 1))
				return (false);
		if (!lock_fork_and_print(table, seat))
			return (false);
	}
	return (true);
}

bool	unlock_forks(t_table *table, int seat)
{
	if (!pthread_mutex_unlock(&(table->seats[seat].fork)))
		return (false);
	if (seat == table->num_of_seats - 1)
		if (!pthread_mutex_unlock(&(table->seats[0].fork)))
			return (false);
	else
		if (!pthread_mutex_unlock(&(table->seats[seat + 1].fork)))
			return (false);
	return (true);
}
