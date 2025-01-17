/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:29:10 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/17 15:43:10 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	check_die(t_philo *philo)
{
	int				i;
	unsigned int	current_time;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		current_time = get_current_time();
		if (current_time - philo[i].last_meal \
		> philo[i].time_to_die && !philo[i].eating)
		{
			pthread_mutex_unlock(philo[i].meal_lock);
			pthread_mutex_lock(philo[i].dead_lock);
			*philo[i].dead = true;
			pthread_mutex_unlock(philo[i].dead_lock);
			pthread_mutex_lock(philo[i].write_lock);
			printf("%u %d died\n", current_time \
			- philo[i].start_time, philo[i].id);
			pthread_mutex_unlock(philo[i].write_lock);
			return (true);
		}
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	return (false);
}

bool	check_num_meals(t_philo *philo)
{
	int		i;
	int		philo_have_done_eating;

	if (philo[0].num_times_to_eat == -1)
		return (false);
	i = 0;
	philo_have_done_eating = 0;
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			philo_have_done_eating++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (philo_have_done_eating == philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = true;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (true);
	}
	return (false);
}

void	*observer(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_die(philo) || check_num_meals(philo))
			break ;
		usleep(50);
	}
	return (NULL);
}
