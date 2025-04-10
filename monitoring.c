/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:10:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/09 21:06:59 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *monitor(void   *info)
{
	int   	 i;
	t_data  *data;

	data = (t_data *)info;
	while (data->philo_dead == FALSE)
	{
		i = 0;
		while (i < data->philos_amount)
		{
			pthread_mutex_lock(&data->death_mutex);
			if ((execution_time(data->start_time) - data->philos[i].last_meal)\
			> data->die_time && data->philos[i].meals_count != \
			data->meals_to_eat)
			{
				print_message(DIE, &data->philos[i]);
				data->philo_dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				break;
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		pthread_mutex_lock(&data->death_mutex);
		printf("philos sated: %d philos amount: %d\n", data->philos_sated, data->philos_amount);
		if (data->philos_sated == data->philos_amount)
		{
			printf("entrou no if do monitor\n");
			pthread_mutex_unlock(&data->death_mutex);
			break;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(1);
	}
	printf("final do monitor\n");
	return (NULL);
}
