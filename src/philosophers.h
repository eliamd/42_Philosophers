/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:20:56 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/09 16:17:15 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

# define ERROR_ARGS "Error -> Arguments not valid\nUsage -> ./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> optional : <number_of_times_each_philosopher_must_eat>"

long	ft_atol(const char *s);
bool	check_args(int argc, char **argv);

#endif
