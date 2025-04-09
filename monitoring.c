/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:10:44 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/09 19:46:04 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *monitor(void   *info)
{
    int     i;
    t_data  *data;

    data = (t_data *)info;
    while (data->philo_dead == 0)
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
        usleep(1);
    }
    return (NULL);
}
