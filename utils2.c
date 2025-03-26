/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:26:12 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/26 16:23:17 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_error(int error_id)
{
	if (error_id == MUTEX_INIT)
		ft_putstr_fd("Error:\nMutex initialization error.\n", 2);
	if (error_id == PHILO_AMOUNT)
		ft_putstr_fd("Error:\nPhilos amount range is from 1 to 200.\n", 2);
	if (error_id == TIME_AMOUNT)
		ft_putstr_fd("Error:\nTime must not be less than 60 ms\n", 2);
	if (error_id == LONG_RANGE)
		ft_putstr_fd("Error:\nArguments must be positive long numbers\n", 2);
	if (error_id == INVALID_CHARACTER)
		ft_putstr_fd("Error:\nYou should only pass numbers as arguments\n", 2);
	if (error_id == WRONG_ARGUMENTS)
		ft_putstr_fd("Error:\nProgram call must be: ./philo \
numbers_of_philosopers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n", 2);
	return (0);
}
