/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:45:16 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/30 14:17:33 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo, int side)
{
	if (side == LEFT)
	{
		pthread_mutex_lock(&philo->data->exec_mutex);
		if (philo->data->philo_dead == TRUE)
			{
				pthread_mutex_unlock(&philo->data->exec_mutex);
				return;
			}
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		print_message(TAKE_FORK, philo);
		pthread_mutex_unlock(&philo->data->exec_mutex);
	}
	else if (side == RIGHT)
	{
		pthread_mutex_lock(&philo->data->exec_mutex);
		if (philo->data->philo_dead == TRUE)
		{
				pthread_mutex_unlock(&philo->data->exec_mutex);
				return;
			}
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		print_message(TAKE_FORK, philo);
		pthread_mutex_unlock(&philo->data->exec_mutex);
	}
}
void	*eating_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	take_forks(philo, LEFT);
	take_forks(philo, RIGHT);
	return (NULL);
}

void	*backup_eating_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
	pthread_mutex_lock(&philo->data->exec_mutex);
    if (philo->left_fork->fork_lock == 0)
    {
        philo->left_fork->fork_lock = 1;
        pthread_mutex_lock(&philo->left_fork->fork_mutex);
        print_message(TAKE_FORK, philo);
    }
    pthread_mutex_unlock(&philo->data->exec_mutex);
    pthread_mutex_lock(&philo->data->exec_mutex);
    if (philo->right_fork->fork_lock == 0)
    {
        philo->right_fork->fork_lock = 1;
        pthread_mutex_lock(&philo->right_fork->fork_mutex);
        print_message(TAKE_FORK, philo);
    }
    pthread_mutex_unlock(&philo->data->exec_mutex);
    return (NULL);
}

