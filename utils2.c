/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:26:12 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/25 15:42:48 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_error(int error_id)
{
	if (error_id == MUTEX_INIT)
		ft_putstr_fd("Error:\nMutex initialization error.", 2);
    if (error_id == PHILO_AMOUNT)
        ft_putstr_fd("Error:\nPhilos amount range is from 1 to 200.", 2);
    if (error_id == TIME_AMOUNT)
        ft_putstr_fd("Error:\nTime must not be less than 60 ms", 2);
    
}