/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbarreto <lbarreto@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:59:01 by lbarreto          #+#    #+#             */
/*   Updated: 2025/04/11 20:10:14 by lbarreto         ###   ########.fr       */
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
# define LEFT 0
# define RIGHT 1
# define LONG_MAX 2147483647
# define LONG_MIN -2147483648

typedef struct s_fork t_fork;
typedef struct s_data t_data;
typedef struct s_philo t_philo;

enum	e_errors {
	MUTEX_INIT = 2,
	PHILO_AMOUNT,
	TIME_AMOUNT,
	LONG_RANGE,
	INVALID_CHARACTER,
	WRONG_ARGUMENTS
};

enum	e_messages {
	EAT,
	TAKE_FORK,
	SLEEP,
	THINK,
	DIE
};

struct s_fork {
	pthread_mutex_t	fork_mutex;
	int				fork_id;
	int				fork_lock;
};

struct	s_data {
	long			start_time;
	int				philos_amount;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				meals_to_eat;
	t_philo			*philos;
	t_fork 			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t eat_mutex;
	pthread_mutex_t	verify_mutex;
	pthread_t		monitor_thread;
	int				philos_sated;
	int				philo_dead;
	int				end_time;
};

struct s_philo {
	long			last_meal;
	int				philo_id;
	int				meals_count;
	pthread_t		philo_thread;
	pthread_mutex_t	philo_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*data;
};


long		execution_time(long start_time);
time_t		get_start_time(void);
long long	ft_atoll(char *nptr);
t_fork		*init_forks(int forks_amount);
t_philo		*init_philos(int philos_amount, t_fork *forks, t_data *data);
t_data		init_data(int argc, char **argv);
int			arguments_verification(int argc, char **argv);
int			range_verification(int argc, char **argv);
int			ft_strlen(char *str);
void		ft_putstr_fd(char *s, int fd);
int			handle_error(int error_id);
int			invalid_arguments_verification(char **argv);
int			execute_verifications(int argc, char **argv);
void		print_message(int message, t_philo *philo);
void		*eating_routine(void *data);
void		init_threads(t_data *data);
void		execute_forks(t_philo *philo);
void		ft_usleep(long time, t_data *data);
void		eat_action(t_philo *philo);
void		take_forks(t_philo *philo, int side);
void    	*monitor(void   *info);
void		destroy_mutex(t_data *data);
void		destroy_data(t_data *data);
#endif