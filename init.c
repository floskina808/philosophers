/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:43:36 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 15:44:11 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_args(t_data *data, int argc, char **argv)
{
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	data->has_meal_limit = (argc == 6);
	data->num_meals = 0;
	if (argc == 6)
		data->num_meals = atoi(argv[5]);
	if (data->num_philos < 1 || data->time_to_die < 0)
		return (0);
	if (data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (0);
	return (1);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i].mutex, NULL) != 0)
			return (0);
		data->forks[i].in_use = 0;
		i++;
	}
	return (1);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = get_timestamp_ms();
		data->philos[i].meals_eaten = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].data = (void *)data;
		i++;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->someone_died = 0;
	data->start_time = get_timestamp_ms();
	if (!init_args(data, argc, argv))
		return (0);
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (0);
	if (!init_mutexes(data) || !init_philos(data))
		return (0);
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philos);
}
