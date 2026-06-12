/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 15:43:59 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 16:24:48 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!is_dead(data))
	{
		if (!philo_cycle(data, philo))
			break ;
	}
	return (NULL);
}
