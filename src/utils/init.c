/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:11:38 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/10 16:35:19 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program program, t_philo *philos)
{
	program.dead_flag = 0;
	program.philos = philos;
	pthread_mutex_init(&program.dead_lock, NULL);
	pthread_mutex_init(&program.meal_lock, NULL);
	pthread_mutex_init(&program.write_lock, NULL);
}
