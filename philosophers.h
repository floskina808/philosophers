/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:47:49 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 16:26:38 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				in_use;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	void			*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_meals;
	int				has_meal_limit;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_fork			*forks;
	t_philo			*philos;
}	t_data;

/* utils.c */
long	get_timestamp_ms(void);
long	get_time_since(long start_time);
void	print_status(t_data *data, int philo_id, const char *status);
int		is_dead(t_data *data);
void	set_dead(t_data *data);

/* init.c */
int		init_data(t_data *data, int argc, char **argv);
void	cleanup(t_data *data);

/* fork.c */
int		take_fork(t_data *data, int philo_id, int fork_id);
void	put_fork(t_data *data, int fork_id);
int		are_forks_available(t_data *data, int left, int right);

/* philo.c */
void	*philosopher_routine(void *arg);
int		philo_cycle(t_data *data, t_philo *philo);
int		take_forks_even(t_data *data, t_philo *philo);
int		take_forks_odd(t_data *data, t_philo *philo);

/* monitor.c */
int		check_deaths(t_data *data);

#endif
