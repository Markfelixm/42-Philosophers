/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:20:03 by marmulle          #+#    #+#             */
/*   Updated: 2023/05/15 20:56:55 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

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
	pthread_t		philo;
	struct timeval	meal_timestamp;
	int				meals_eaten;

	pthread_mutex_t	fork;
}					t_seat;

typedef struct s_table
{
	int				num_of_seats;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;

	struct timeval	init_timestamp;

	t_seat			seats[200];
}	t_table;

// Philosopher
bool	has_died(t_table *table, int seat);
bool	lives(t_table *table, int seat);
bool	eats(t_table *table, int seat);

// Memory
bool	init_table(int ac, char **av, t_table *table);
bool	init_seats(t_table *table);

// Time
long	time_since_timestamp(struct timeval ts);

// Print
bool	print_activity(t_table *table, int seat, t_activity activity);
bool	lock_fork_and_print(t_table *table, int seat);

// Utility
int		ft_atoi(const char *str);

#endif
