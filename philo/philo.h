/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:03 by marmulle          #+#    #+#             */
/*   Updated: 2023/08/05 19:21:25 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef USLEEP_INTERVAL
#  define USLEEP_INTERVAL 500
# endif

typedef struct s_seat	t_seat;
typedef struct s_table	t_table;
typedef long long		t_ll;

typedef enum e_tri
{
	FALSE = 0,
	TRUE = 1,
	ERROR = 2
}	t_tri;

typedef enum e_actvity
{
	TAKEN_FORK,
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	pthread_mutex_t	meal_ts_mutex;
	t_ll			meal_ts;
	int				meals_eaten;

	t_table			*table;
}	t_seat;

typedef struct s_table
{
	int				num_of_seats;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;

	t_ll			init_ts;

	t_seat			seats[200];

	pthread_mutex_t	death_mutex;
	t_tri			death_occured;

	pthread_mutex_t	gate;
	pthread_mutex_t	print;
}	t_table;

// philo.c
t_tri	monitor_philosophers(t_table *table);

// activity.c
t_tri	lives(t_seat *seat);
t_tri	init_routine(t_seat *seat);
t_tri	eats(t_seat *seat);
t_tri	is_done_eating(t_seat *seat);
t_tri	is_lonely_philo(t_seat *seat);

// memory.c
t_tri	init_table(t_table *table, int ac, char **av);
t_tri	init_seats(t_table *table);
t_tri	join_threads(t_table *table, int until);
t_tri	destroy_seats(t_seat *seats, int until);
t_tri	destroy_table(t_table *table);

// time.c
t_ll	time_since_timestamp(t_ll ts);
int		ft_usleep(t_ll us);
t_ll	get_ms(struct timeval *ts);
t_ll	get_current_ms(void);

// print.c
t_tri	print_activity(t_seat *seat, t_activity activity);

// forks.c
void	assign_forks(t_seat *seat);
t_tri	lock_forks(t_seat *seat);
t_tri	unlock_forks(t_seat *seat);

// death.c
t_tri	set_died_state(t_table *table);
t_tri	has_anyone_died(t_table *table);
t_tri	has_died(t_seat *seat);

// atoi.c
int		ft_atoi(const char *str);

#endif
