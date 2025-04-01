/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:45:16 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/01 20:29:12 by lbarreto         ###   ########.fr       */
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
void	execute_action(t_philo *philo, int action)
{
	if (action == EAT)
	{
		pthread_mutex_lock(&philo->data->exec_mutex);
		philo->last_meal = execution_time(philo->data->start_time);
		pthread_mutex_unlock(&philo->data->exec_mutex);
		print_message(EAT, philo);
		ft_usleep(philo->data->eat_time, philo->data);
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
		pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	}
	if (action == SLEEP)
	{
		print_message(SLEEP, philo);
		ft_usleep(philo->data->sleep_time, philo->data);
	}
}

void	*eating_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		take_forks(philo, LEFT);
		take_forks(philo, RIGHT);
		execute_action(philo, EAT);
		execute_action(philo, SLEEP);
	}
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

