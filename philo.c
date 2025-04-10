/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:58:49 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/09 20:25:48 by lbarreto         ###   ########.fr       */
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
	
	printf("Start time: %ld\nPhilos_amount: %d\nDie_time: %ld\nEat_time: %ld\n Sleep_time: %ld\n Meals_to_eat: %d\n", data.start_time, data.philos_amount, data.die_time, data.eat_time, data.sleep_time, data.meals_to_eat);
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