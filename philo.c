/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:58:49 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/11 22:12:55 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int i;

	i = 0;
	if (execute_verifications(argc, argv) == 0)
		return (0);
	data = init_data(argc, argv);

	init_threads(&data);
 	while(i < data.philos_amount)
 	{
 		pthread_join(data.philos[i].philo_thread, NULL);
 		i++;
 	}
	pthread_join(data.monitor_thread, NULL);
	destroy_mutex(&data);
	destroy_data(&data);
}
