/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:32:08 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/16 14:02:31 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	dead_check(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(philo->dead_lock);
	is_dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_check(philo))
	{
		if (philo_routine(philo))
			break;
	}
	return (arg);
}

int	thread_create(t_program program, pthread_mutex_t *forks)
{
	int				i;
	pthread_t		observer_thread;

	if (pthread_create(&observer_thread, NULL, observer, program.philos) != 0)
		return (destroy_mutexes(&program, forks), 1);
	i = 0;
	while (i < program.philos[0].num_of_philos)
	{
		if (pthread_create(&program.philos[i].thread, NULL, \
		routine, &program.philos[i]) != 0)
			return (destroy_mutexes(&program, forks), 1);
		i++;
	}
	if (pthread_join(observer_thread, NULL) != 0)
		return (destroy_mutexes(&program, forks), 1);
	i = 0;
	while (i < program.philos[0].num_of_philos)
	{
		if (pthread_join(program.philos[i].thread, NULL) != 0)
			return (destroy_mutexes(&program, forks), 1);
		i++;
	}
	return (0);
}
