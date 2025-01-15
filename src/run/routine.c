/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:47:26 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/14 17:48:03 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	eat(t_philo *philo)
{
	if (dead_check(philo))
		return (1);
	take_forks(philo);
	if (philo->num_of_philos == 1)
		return (ft_usleep(philo->time_to_die), 1);
	if (dead_check(philo))
		return (pthread_mutex_unlock(philo->l_fork), \
				pthread_mutex_unlock(philo->r_fork), 1);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	philo->eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d is eating\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (dead_check(philo))
		return (1);
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d is sleeping\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (dead_check(philo))
		return (1);
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d is thinking\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (dead_check(philo))
		return (1);
	pthread_mutex_lock(philo->l_fork);
	if (dead_check(philo))
		return (pthread_mutex_unlock(philo->l_fork), 1);
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d has taken a fork\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	if (philo->num_of_philos == 1)
		return (pthread_mutex_unlock(philo->l_fork), 1);
	pthread_mutex_lock(philo->r_fork);
	if (dead_check(philo))
		return (pthread_mutex_unlock(philo->l_fork) \
		, pthread_mutex_unlock(philo->r_fork), 1);
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d has taken a fork\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	return (0);
}
