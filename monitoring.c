/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:10:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/12 04:37:57 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *info)
{
	int		i;
	t_data	*data;

	data = (t_data *)((t_philo *)info)->data;
	while (data->philo_dead == FALSE)
	{
		i = 0;
		while (i < data->philos_amount)
		{
			verify_death(data, &i);
			i++;
		}
		pthread_mutex_lock(&data->eat_mutex);
		if (data->end_time == TRUE)
		{
			pthread_mutex_unlock(&data->eat_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->eat_mutex);
		usleep(1);
	}
	return (NULL);
}

void	print_death(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = execution_time(philo->data->start_time);
	printf("%ld philo %d died\n", time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	verify_death(t_data *data, int *i)
{
	pthread_mutex_lock(&data->eat_mutex);
	if ((execution_time(data->start_time) - data->philos[*i].last_meal) \
	> data->die_time && data->philos[*i].meals_count != \
	data->meals_to_eat)
	{
		data->philo_dead = TRUE;
		pthread_mutex_unlock(&data->eat_mutex);
		print_death(&data->philos[*i]);
		*i = data->philos_amount;
	}
	else
		pthread_mutex_unlock(&data->eat_mutex);
}
