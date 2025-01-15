/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:34:28 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/15 21:31:43 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];

	program.dead_flag = 0;
	if (!check_args(argc, argv))
		return (printf(ERROR_ARGS), 1);
	if (!init_forks(forks, ft_atoi(argv[1])))
		return (printf(ERROR_INIT_FORKS), 1);
	if (!init_program(&program, philos))
	{
		destroy_mutexes(&program, forks);
		return (printf(ERROR_INIT_PROGRAM), 1);
	}
	init_philos(philos, &program, forks, argv);
	if (philos->num_of_philos == 1)
		single_philo(philos);
	else
	{
		thread_create(program, forks);
		cleanup_program(&program, forks);
	}
	return (0);
}
