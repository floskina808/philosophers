/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:43:44 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 15:44:11 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	check_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo num_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [num_meals]\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc))
		return (1);
	if (!init_data(&data, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!create_threads(&data))
	{
		printf("Error: Failed to create thread\n");
		cleanup(&data);
		return (1);
	}
	while (!check_deaths(&data))
		usleep(1000);
	if (!join_threads(&data))
	{
		printf("Error: Failed to join thread\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
