/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faiello <faiello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 16:10:00 by faiello           #+#    #+#             */
/*   Updated: 2026/06/12 16:24:48 by faiello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	wait_for_forks(t_data *data, int fork1, int fork2)
{
	while (!are_forks_available(data, fork1, fork2))
	{
		if (is_dead(data))
			return (0);
		usleep(100);
	}
	return (!is_dead(data));
}

static int	take_both_forks(t_data *data, int philo_id, int f1, int f2)
{
	if (!take_fork(data, philo_id, f1))
		return (0);
	if (is_dead(data))
	{
		put_fork(data, f1);
		return (0);
	}
	if (!take_fork(data, philo_id, f2))
	{
		put_fork(data, f1);
		return (0);
	}
	return (1);
}

int	take_forks_even(t_data *data, t_philo *philo)
{
	if (!wait_for_forks(data, philo->left_fork, philo->right_fork))
		return (0);
	if (!take_both_forks(data, philo->id, philo->left_fork,
			philo->right_fork))
		return (0);
	return (1);
}

int	take_forks_odd(t_data *data, t_philo *philo)
{
	if (!wait_for_forks(data, philo->right_fork, philo->left_fork))
		return (0);
	if (!take_both_forks(data, philo->id, philo->right_fork,
			philo->left_fork))
		return (0);
	return (1);
}
