/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:20:56 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/13 19:10:44 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define PHILOS_MAX 200

# define ERROR_ARGS "Error -> Arguments not valid\nUsage -> ./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> optional : <number_of_times_each_philosopher_must_eat>"
# define ERROR_INIT_FORKS "Error -> Error while initation of forks mutexex\n"
# define ERROR_INIT_PROGRAM "Error -> Error while initation of program \
structure (and mutexex)\n"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	unsigned int	last_meal;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	bool			dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	bool			dead_flag;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}				t_program;

//atol.c
long			ft_atol(const char *s);
int				ft_atoi(const char *nptr);

//gettime.c
unsigned int	get_current_time(void);

//check_args.c
bool			check_args(int argc, char **argv);

//init.c
int				init_program(t_program *program, t_philo *philos);
int				init_forks(pthread_mutex_t *forks, int philo_num);
void			init_philos(t_philo *philos, t_program *program, \
pthread_mutex_t *forks, char **argv);

//routine.c
void			eat(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			take_forks(t_philo *philo);

//observer.c
void			*observer(void *arg);

//thread_run.c
int				thread_create(t_program program, pthread_mutex_t *forks);

#endif
