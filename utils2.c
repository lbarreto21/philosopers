/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:26:12 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 04:30:27 by lbarreto         ###   ########.fr       */
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

void	print_message(int message, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->eat_mutex);
	if (philo->data->philo_dead == TRUE)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	time = execution_time(philo->data->start_time);
	if (message == TAKE_FORK)
		printf("%ld philo %d has taken a fork\n", time, philo->philo_id);
	if (message == EAT)
		printf("%ld philo %d is eating\n", time, philo->philo_id);
	if (message == SLEEP)
		printf("%ld philo %d is sleeping\n", time, philo->philo_id);
	if (message == THINK)
		printf("%ld philo %d is thinking\n", time, philo->philo_id);
	if (message == DIE)
		printf("%ld philo %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_usleep(long time, t_data *data)
{
	long	start_time;

	(void)data;
	start_time = get_start_time();
	while ((get_start_time() - start_time) < time)
		usleep(200);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_amount)
	{
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		i++;
	}
}

void	destroy_data(t_data *data)
{
	free(data->forks);
	free(data->philos);
}
