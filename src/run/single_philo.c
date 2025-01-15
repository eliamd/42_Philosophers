/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:32:08 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/15 21:32:54 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	single_philo(t_philo *philo)
{
	printf("0 1 has taken a fork\n");
	ft_usleep(philo->time_to_die);
	printf("%u 1 died\n", philo->time_to_die);
}
