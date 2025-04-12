/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:55:04 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/11 22:11:05 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(int philos_amount, t_fork *forks, t_data *data)
{
	t_philo *philos;
	int		i;

	i = -1;
	philos = (t_philo *)malloc(philos_amount * sizeof(t_philo));
	while (++i < philos_amount)
	{
		philos[i].philo_id = i + 1;
		philos[i].meals_count = 0;
		philos[i].last_meal = 0;
		if (i % 2 == 0)
		{
			philos[i].left_fork = &forks[i];
			philos[i].right_fork = &forks[(i + 1) % philos_amount];
		}
		else
		{
			philos[i].left_fork = &forks[(i + 1) % philos_amount];
			philos[i].right_fork = &forks[i];
		}
		philos[i].data = data;
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
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
			handle_error(MUTEX_INIT);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
t_data	init_data(int argc, char **argv)
{
	t_data	data;

	data.philo_dead = FALSE;
	data.philos_amount = (int)ft_atoll(argv[1]);
	data.forks = init_forks(data.philos_amount);
	data.die_time = (long)ft_atoll(argv[2]);
	data.eat_time = (long)ft_atoll(argv[3]);
	data.sleep_time = (long)ft_atoll(argv[4]);
	if (argc == 6)
		data.meals_to_eat = (int)ft_atoll(argv[5]);
	else
		data.meals_to_eat = -1;
	data.philos_sated = 0;
	data.philos = init_philos(data.philos_amount, data.forks, &data);
	pthread_mutex_init(&data.print_mutex, NULL);
	pthread_mutex_init(&data.death_mutex, NULL);
	pthread_mutex_init(&data.eat_mutex, NULL);
	pthread_mutex_init(&data.verify_mutex, NULL);
	data.start_time = get_start_time();
	
	data.end_time = FALSE;
	return (data);
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_amount)
	{
		pthread_create(&data->philos[i].philo_thread, NULL, eating_routine, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor, &data->philos[0]);
}