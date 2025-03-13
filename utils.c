/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:39:36 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/13 15:17:00 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(char *nptr)
{
	long	nbr;
	int		i;
	int		n;

	nbr = 0;
	i = 0;
	n = 1;
	while (nptr[i] == '\n' || nptr[i] == '\t' || nptr[i] == '\r'
		|| nptr[i] == ' ' || nptr[i] == '\v' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-')
	{
		n = -n;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = (nbr * 10) + (nptr[i] - '0');
		i++;
	}
	return (nbr * n);
}

long	get_time_in_ms(void)
{
	struct timeval	time;
	long				time_in_ms;

	if (gettimeofday(&time, NULL) == 0)
	{
		time_in_ms = time.tv_sec * 1000;
		return (time_in_ms);
	}
	return (-1);
}