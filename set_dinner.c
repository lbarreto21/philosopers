/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:55:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/19 19:43:05 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(int philos_amount, t_fork *forks)
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
		if (i % 2 == 0)
		{
			philos[i].left_fork = &forks[i].fork_mutex;
			philos[i].right_fork = &forks[(i + 1) % philos_amount].fork_mutex;
		}
		else
		{
			philos[i].left_fork = &forks[(i + 1) % philos_amount].fork_mutex;
			philos[i].right_fork = &forks[i].fork_mutex;
		}
		i++;
	}
	return (philos);
}

t_fork	*init_forks(int forks_amount)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * forks_amount);
	if (!forks)
		return (NULL);
	while (i < forks_amount)
	{
		forks[i].fork_id = i + 1;
		forks[i].fork_lock = 0;
		if (pthread_mutex_init(&forks[i].fork_mutex, NULL) != 0)
		{
			free(forks);
			//handle_error(MUTEX_INIT);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.start_time = get_start_time();
	data.philos_amount = (int)ft_atol(argv[1]);
	data.forks = init_forks(data.philos_amount);
	data.die_time = ft_atol(argv[2]);
	data.eat_time = ft_atol(argv[3]);
	data.sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		data.meals_to_eat = (int)ft_atol(argv[5]);
	else
		data.meals_to_eat = -1;
	data.philos = init_philos(data.philos_amount, data.forks);

	return (data);
}