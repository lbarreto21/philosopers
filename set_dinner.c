/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:55:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/13 17:03:44 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(int philos_amount, pthread_mutex_t *forks)
{
	t_philo *philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(philos_amount * sizeof(t_philo));
	if (!philos)
		return (NULL);
	while (i < philos_amount)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_count = 0;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % philos_amount];
		i++;
	}
}

t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.start_time = get_time_in_ms();
	data.philos_amount = (int)ft_atol(argv[1]);
	data.die_time = ft_atol(argv[2]);
	data.eat_time = ft_atol(argv[3]);
	data.sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		data.meals_to_eat = (int)ft_atol(argv[5]);
	else
		data.meals_to_eat = -1;
	data.philos = init_philos(data.philos_amount);

}