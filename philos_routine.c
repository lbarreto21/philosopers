/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:45:16 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/02 21:21:55 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo, int side)
{
	if (side == LEFT)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->philo_dead == TRUE)
			{
				pthread_mutex_unlock(&philo->data->death_mutex);
				return;
			}
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		print_message(TAKE_FORK, philo);
	}
	else if (side == RIGHT)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->philo_dead == TRUE)
		{
				pthread_mutex_unlock(&philo->data->death_mutex);
				return;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		print_message(TAKE_FORK, philo);
	}
}
void	execute_action(t_philo *philo, int action)
{
	/* pthread_mutex_lock(&philo->data->eat_mutex);
	if (philo->data->philo_dead == 1 || philo->data->philos_sated == philo->data->philos_amount)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->data->eat_mutex); */
	if (action == EAT)
	{
		pthread_mutex_lock(&philo->data->eat_mutex);
		philo->last_meal = execution_time(philo->data->start_time);
		philo->meals_count++;
		pthread_mutex_unlock(&philo->data->eat_mutex);
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
	if (action == THINK)
		print_message(THINK, philo);
}

void	*eating_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_id % 2 == 0)
		usleep (2000);
	while (1)
	{
		take_forks(philo, LEFT);
		take_forks(philo, RIGHT);
		execute_action(philo, EAT);
		execute_action(philo, SLEEP);
		execute_action(philo, THINK);
	}
	return (NULL);
}
