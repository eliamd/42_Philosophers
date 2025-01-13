/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:29:10 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/13 19:45:33 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

//TODO finir de debuguer

static bool	check_die(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		if (get_current_time() - philo[i].last_meal > philo[i].time_to_die)
		{
			pthread_mutex_lock(philo[i].dead_lock);
			philo[i].dead = true;
			pthread_mutex_unlock(philo[i].dead_lock);
			pthread_mutex_lock(philo[i].write_lock);
			printf("%u %d died\n", get_current_time() \
			- philo[i].start_time, philo[i].id);
			pthread_mutex_unlock(philo[i].write_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_num_meals(t_philo *philo)
{
	int		i;
	int		philo_have_done_eating;

	i = 0;
	philo_have_done_eating = 0;
	if (philo->num_times_to_eat == -1)
		return (false);
	while (i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			philo_have_done_eating++;
		pthread_mutex_unlock(philo->meal_lock);
		i++;
	}
	if (philo_have_done_eating == philo->num_of_philos)
	{
		printf("pcacahilo_have_done_eating : %d == philo->.num_of_philos : %d\n", philo_have_done_eating, philo[0].num_of_philos);
		pthread_mutex_lock(philo->dead_lock);
		printf("ICICIICI 2\n");
		(*philo).dead = true;
		pthread_mutex_unlock(philo->dead_lock);
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
		printf("========================\n");
		if (check_die(philo) || check_num_meals(philo))
		{
			printf("============ DEAD ============\n");
			break ;
		}
	}
	return (arg);
}
