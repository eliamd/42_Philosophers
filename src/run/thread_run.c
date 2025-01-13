/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:32:08 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/13 19:26:12 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	dead_check(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->dead)
		return (pthread_mutex_unlock(philo->dead_lock), true);
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(100);
	while (!dead_check(philo))
	{
		take_forks(philo);
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	thread_create(t_program program, pthread_mutex_t *forks)
{
	int				i;
	pthread_t		observer_thread;

	(void)forks;
	i = 0;
	if (pthread_create(&observer_thread, NULL, observer, &program.philos) != 0)
		return (1);
	while (i < program.philos[0].num_of_philos)
	{
		if (pthread_create(&program.philos[i].thread, NULL, \
		routine, &program.philos[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(observer_thread, NULL) != 0)
		return (1);
	while (i < program.philos[0].num_of_philos)
	{
		if (pthread_join(program.philos[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
