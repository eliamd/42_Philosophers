/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:19:36 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/09 16:17:40 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (false);
	if ((ft_atol(argv[1]) > 200 || ft_atol(argv[1]) < 1) && \
		(ft_atol(argv[2]) > INT_MAX || ft_atol(argv[2]) < 1) && \
		(ft_atol(argv[3]) > INT_MAX || ft_atol(argv[3]) < 1) && \
		(ft_atol(argv[4]) > INT_MAX || ft_atol(argv[4]) < 1))
		return (false);
	if (argc == 6)
	{
		if (ft_atol(argv[5]) > INT_MAX || ft_atol(argv[5]) < 1)
			return (false);
	}
	return (true);
}
