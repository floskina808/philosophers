/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:43:30 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 15:44:11 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_fork(t_data *data, int philo_id, int fork_id)
{
	pthread_mutex_lock(&data->forks[fork_id].mutex);
	if (is_dead(data))
	{
		pthread_mutex_unlock(&data->forks[fork_id].mutex);
		return (0);
	}
	data->forks[fork_id].in_use = 1;
	pthread_mutex_unlock(&data->forks[fork_id].mutex);
	print_status(data, philo_id, "has taken a fork");
	return (1);
}

void	put_fork(t_data *data, int fork_id)
{
	pthread_mutex_lock(&data->forks[fork_id].mutex);
	data->forks[fork_id].in_use = 0;
	pthread_mutex_unlock(&data->forks[fork_id].mutex);
}

int	are_forks_available(t_data *data, int left, int right)
{
	int	available;

	pthread_mutex_lock(&data->forks[left].mutex);
	available = !data->forks[left].in_use;
	pthread_mutex_unlock(&data->forks[left].mutex);
	if (!available)
		return (0);
	pthread_mutex_lock(&data->forks[right].mutex);
	available = !data->forks[right].in_use;
	pthread_mutex_unlock(&data->forks[right].mutex);
	return (available);
}
