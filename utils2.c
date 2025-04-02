/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:26:12 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/02 18:34:00 by lbarreto         ###   ########.fr       */
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
	
	pthread_mutex_lock(&philo->data->print_mutex);
	time = execution_time(philo->data->start_time);
	if (message == TAKE_FORK && philo->data->philo_dead == 0)
		printf("%ld philo %d has taken a fork\n", time, philo->philo_id);
	if (message == EAT && philo->data->philo_dead == 0)
		printf("%ld philo %d is eating\n", time, philo->philo_id);	
	if (message == SLEEP && philo->data->philo_dead == 0)
		printf("%ld philo %d is sleeping\n", time, philo->philo_id);
	if (message == THINK && philo->data->philo_dead == 0)
		printf("%ld philo %d is thinking\n", time, philo->philo_id);
	if (message == DIE && philo->data->philo_dead == 0)
	{
		printf("%ld philo %d died\n", time, philo->philo_id);
		philo->data->philo_dead = 1;
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

/*void	ft_usleep(long time, t_data *data)
{
	long	start_time;

	(void)data;
	start_time = get_start_time();
	while ((get_start_time() - start_time) < time)
	{
		//if ()
			//break;
		//usleep(200);
	
		//else
		//{
			//while (get_start_time() - start_time < time)
			//{
				//usleep(1);
			//}
		//}
//	}*/

void	ft_usleep(long time)
{
	long	finish_time;
	long	current_time;

	current_time = get_start_time();
	finish_time = current_time + time;
	while (current_time < finish_time)
	{
		usleep(((finish_time - current_time) * 1000) / 2);
		current_time = get_start_time();
	}
}