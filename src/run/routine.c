/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:47:26 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/13 23:58:14 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void    eat(t_philo *philo)
{
    if (dead_check(philo))
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return;
    }
    if (dead_check(philo))
        return ;
    take_forks(philo);
    if (dead_check(philo))
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        return ;
    }
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);

    pthread_mutex_lock(philo->write_lock);
    printf("%u %d is eating\n", get_current_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->write_lock);

    usleep(philo->time_to_eat * 1000);
    if (!dead_check(philo))
    {
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
    }
}

void	sleeping(t_philo *philo)
{
	if (dead_check(philo))
		return;
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d is sleeping\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
	usleep(philo->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	if (dead_check(philo))
		return;
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d is thinking\n", get_current_time() \
	- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	take_forks(t_philo *philo)
{
	if (dead_check(philo))
		return;
	pthread_mutex_lock(philo->l_fork);
	if (dead_check(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return;
	}
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);

	pthread_mutex_lock(philo->r_fork);
	if (dead_check(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return;
	}
	pthread_mutex_lock(philo->write_lock);
	printf("%u %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}
