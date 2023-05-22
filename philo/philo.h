/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:03 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/19 22:07:25 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_seat	t_seat;
typedef struct s_table	t_table;

typedef enum e_actvity
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_activity;

typedef struct s_seat
{
	int				pos;
	pthread_t		philo;

	pthread_mutex_t	fork;
	struct timeval	meal_ts;
	int				meals_eaten;

	bool			error;
	t_table			*table;
}	t_seat;

typedef struct s_table
{
	int				num_of_seats;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;

	struct timeval	init_ts;

	t_seat			seats[200];
}	t_table;

// Philosopher
bool	monitor_philosophers(t_table *table);
bool	has_died(t_table *table, int seat);
void	lives(t_seat *seat);
bool	eats(t_seat *seat);
bool	lock_forks(t_seat *seat);
bool	unlock_forks(t_table *table, int pos);

// Memory
bool	init_table(int ac, char **av, t_table *table);
bool	init_seats(t_table *table);
bool	destroy_all_humans(t_table *table);

// Time
long	time_since_timestamp(struct timeval *ts);

// Print
bool	print_activity(t_seat *seat, t_activity activity);

// Utility
int		ft_atoi(const char *str);

#endif
