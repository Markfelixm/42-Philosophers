/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:03 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/25 18:40:03 by marmulle         ###   ########.fr       */
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
	pthread_mutex_t	meals_mutex;
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

	pthread_mutex_t	died_mutex;
	bool			has_anyone_died;

	struct timeval	init_ts;

	t_seat			seats[200];
}	t_table;

// philo.c
bool	monitor_philosophers(t_table *table);

// activity.c
bool	has_died(t_table *table, int seat);
void	lives(t_seat *seat);
bool	eats(t_seat *seat);
bool	is_done_eating(t_seat *seat);
bool	is_lonely_philo(t_seat *seat);

// memory.c
bool	init_table(t_table *table, int ac, char **av);
bool	init_seats(t_table *table);
bool	destroy_all_humans(t_table *table);

// time.c
long	time_since_timestamp(struct timeval *ts);

// print.c
bool	print_activity(t_seat *seat, t_activity activity);

// mutex.c
bool	lock_forks(t_seat *seat);
bool	unlock_forks(t_table *table, int pos);
void	set_died_state(t_seat *seat);
bool	has_anyone_died(t_seat *seat);

// atoi.c
int		ft_atoi(const char *str);

#endif
