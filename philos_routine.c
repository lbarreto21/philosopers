/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:45:16 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/29 19:10:47 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eating_routine(void *data)
{
    t_philo *philo;
    philo = (t_philo *)data;

    while(1)
    {
        printf("entrou na thread\n");
	    pthread_mutex_lock(&philo->data->exec_mutex);
        printf("Deu lock no mutex\n");
        if (philo->left_fork->fork_lock == 0)
        {
            philo->left_fork->fork_lock = 1;
            pthread_mutex_lock(&philo->left_fork->fork_mutex);
            printf("entrou no if\n");
            print_message(TAKE_FORK, philo);
            pthread_mutex_unlock(&philo->data->exec_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->data->exec_mutex);
    }
    return (NULL);
}