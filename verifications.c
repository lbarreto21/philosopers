/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:21 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/25 15:48:49 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arguments_verification(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	range_verification(int argc, char **argv)
{
	int			i;
	long long	number;

	i = 1;
	while (i < argc)
	{
		number = ft_atoll(argv[i]);
		if (number < 1 || number > LONG_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	invalid_arguments_verification(char **argv)
{
	int	i;

	i = 2;
	if (ft_atoll(argv[1]) < 1 || ft_atoll(argv[1]) > 200)
		return (handle_error(PHILO_AMOUNT));
	while (i < 5)
	{
		if (ft_atoll(argv[i]) < 60)
			return (handle_error(TIME_AMOUNT));
		i++;
	}
	return (1);
}

