/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:45:16 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 04:53:46 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo, int side)
{
	if (side == LEFT)
	{
		pthread_mutex_lock(&philo->data->eat_mutex);
		if (philo->data->philo_dead == TRUE)
		{
			pthread_mutex_unlock(&philo->data->eat_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_mutex_lock(&philo->left_fork->fork_mutex);
		print_message(TAKE_FORK, philo);
	}
	else if (side == RIGHT)
	{
		pthread_mutex_lock(&philo->data->eat_mutex);
		if (philo->data->philo_dead == TRUE)
		{
			pthread_mutex_unlock(&philo->data->eat_mutex);
			pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->eat_mutex);
		pthread_mutex_lock(&philo->right_fork->fork_mutex);
		print_message(TAKE_FORK, philo);
	}
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_meal = execution_time(philo->data->start_time);
	philo->meals_count++;
	if (philo->meals_count == philo->data->meals_to_eat)
		philo->data->philos_sated++;
	if (philo->data->philos_sated == philo->data->philos_amount)
		philo->data->end_time = TRUE;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	print_message(EAT, philo);
	ft_usleep(philo->data->eat_time, philo->data);
	pthread_mutex_unlock(&philo->left_fork->fork_mutex);
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
}

void	execute_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	if (philo->data->philo_dead == TRUE || \
	philo->data->philos_sated == philo->data->philos_amount)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	take_forks(philo, LEFT);
	if (philo->data->philos_amount > 1)
		take_forks(philo, RIGHT);
	else
		pthread_mutex_unlock(&philo->left_fork->fork_mutex);
}

void	execute_action(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	if (philo->data->philo_dead == TRUE || \
	philo->data->philos_sated == philo->data->philos_amount)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	if (action == EAT)
		eat_action(philo);
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
	while (philo->meals_count != philo->data->meals_to_eat && \
	philo->data->philo_dead == FALSE)
	{
		execute_forks(philo);
		if (philo->data->philos_amount == 1)
			break ;
		if (philo->data->philo_dead == TRUE)
		{
			pthread_mutex_unlock(&philo->left_fork->fork_mutex);
			pthread_mutex_unlock(&philo->right_fork->fork_mutex);
		}
		execute_action(philo, EAT);
		execute_action(philo, SLEEP);
		execute_action(philo, THINK);
	}
	return (NULL);
}
