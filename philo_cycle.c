/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:10:00 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 16:24:48 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eat_action(t_data *data, t_philo *philo)
{
	philo->last_meal_time = get_timestamp_ms();
	philo->meals_eaten++;
	print_status(data, philo->id, "is eating");
	usleep(data->time_to_eat * 1000);
	put_fork(data, philo->left_fork);
	put_fork(data, philo->right_fork);
	return (1);
}

static void	sleep_and_think(t_data *data, t_philo *philo)
{
	if (is_dead(data))
		return ;
	print_status(data, philo->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	if (!is_dead(data))
		print_status(data, philo->id, "is thinking");
}

int	philo_cycle(t_data *data, t_philo *philo)
{
	print_status(data, philo->id, "is thinking");
	if (philo->id % 2 == 0)
	{
		if (!take_forks_even(data, philo))
			return (0);
	}
	else
	{
		if (!take_forks_odd(data, philo))
			return (0);
	}
	if (!eat_action(data, philo))
		return (0);
	sleep_and_think(data, philo);
	return (1);
}
