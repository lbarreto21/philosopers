/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:59:01 by lbarreto          #+#    #+#             */
/*   Updated: 2025/03/26 16:46:36 by lbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define LONG_MAX 2147483647
# define LONG_MIN -2147483648

enum	e_errors {
	MUTEX_INIT = 2,
	PHILO_AMOUNT,
	TIME_AMOUNT,
	LONG_RANGE,
	INVALID_CHARACTER,
	WRONG_ARGUMENTS
};

typedef struct s_philo {
	int	philo_id;
	int	meals_count;
	pthread_t philo_thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_fork {
	pthread_mutex_t	fork_mutex;
	int				fork_id;
	int				fork_lock;
} t_fork;

typedef struct	s_data {
	long			start_time;
	int				philos_amount;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				meals_to_eat;
	t_philo			*philos;
	t_fork 			*forks;
	pthread_mutex_t	print_mutex;
} t_data;

long		execution_time(long start_time);
time_t		get_start_time(void);
long long	ft_atoll(char *nptr);
t_fork		*init_forks(int forks_amount);
t_philo		*init_philos(int philos_amount, t_fork *forks);
t_data		init_data(int argc, char **argv);
int			arguments_verification(int argc, char **argv);
int			range_verification(int argc, char **argv);
int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
int			handle_error(int error_id);
int			invalid_arguments_verification(char **argv);
int			execute_verifications(int argc, char **argv);

#endif