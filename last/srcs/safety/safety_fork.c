/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:30:28 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 07:12:28 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_one_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->status = 0;
	pthread_mutex_unlock(&fork->fork);
}

void	safe_unlock_forks(t_philo *philo)
{
	unlock_one_fork(philo->left);
	unlock_one_fork(&philo->right);
}

int	safe_take(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	if (fork->status == 0)
	{
		fork->status = 1;
		pthread_mutex_unlock(&fork->fork);
		return (1);
	}
	pthread_mutex_unlock(&fork->fork);
	return (0);
}

int	safe_forks(t_philo *philo, t_fork *left, t_fork *right)
{
	check_life(philo);
	if (check_end(philo) == 1)
		return (0);
	if (safe_take(left) == 0)
	{
		usleep(500);
		return (0);
	}
	if (safe_take(right) == 0)
	{
		unlock_one_fork(left);
		usleep(500);
		return (0);
	}
	return (1);
}
