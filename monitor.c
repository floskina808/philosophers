/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:43:50 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 15:44:11 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_philo_death(t_data *data, int i)
{
	long	time_since_meal;

	time_since_meal = get_timestamp_ms() - data->philos[i].last_meal_time;
	if (time_since_meal > data->time_to_die)
	{
		set_dead(data);
		print_status(data, data->philos[i].id, "died");
		return (1);
	}
	return (0);
}

static int	all_ate_enough(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->num_meals)
			return (0);
		i++;
	}
	return (1);
}

int	check_deaths(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_philo_death(data, i))
			return (1);
		i++;
	}
	if (data->has_meal_limit && all_ate_enough(data))
	{
		set_dead(data);
		return (1);
	}
	return (0);
}
