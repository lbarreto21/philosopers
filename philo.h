/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:59:01 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/13 17:07:48 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo {
	int	philo_id;
	int	meals_count;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_fork {
	pthread_mutex_t	fork_mutex;
	
} t_fork;

typedef struct	s_data {
	long			start_time;
	int				philos_amount;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				meals_to_eat;
	t_philo			*philos;
	pthread_mutex_t *forks;
} t_data;

long	get_time_in_ms(void);
int		ft_atol(char *nptr);

#endif