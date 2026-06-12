/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:48:06 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 15:48:07 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_time_since(long start_time)
{
	return (get_timestamp_ms() - start_time);
}

void	print_status(t_data *data, int philo_id, const char *status)
{
	long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_time_since(data->start_time);
	printf("%ld %d %s\n", timestamp, philo_id, status);
	pthread_mutex_unlock(&data->print_mutex);
}

int	is_dead(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}

void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}
