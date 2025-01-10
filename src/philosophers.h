/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:20:56 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/10 16:01:20 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>

# define ERROR_ARGS "Error -> Arguments not valid\nUsage -> ./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> optional : <number_of_times_each_philosopher_must_eat>"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meal_eaten;
	unsigned int	last_meal;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	start_time;
	int				num_of_philos;
	int				num_time_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	t_philo			philos;
}				t_program;


long	ft_atol(const char *s);
bool	check_args(int argc, char **argv);

#endif
