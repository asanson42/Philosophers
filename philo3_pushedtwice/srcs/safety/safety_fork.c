/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 02:45:25 by asanson           #+#    #+#             */
/*   Updated: 2022/05/26 05:52:14 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	verif_left_fork(t_philo *philo)
{
	int		fork;
	t_philo	*next;

	if (philo->n == philo->data->num_of_philo)
		next = &philo->data->philo[0];
	else
		next = &philo->data->philo[philo->n + 1];
	pthread_mutex_lock(&next->fork);
	fork = next->latch;
	if (fork == 0)
		next->latch = 1;
	pthread_mutex_unlock(&next->fork);
	return (fork);
}
*/
int	verif_right_fork(t_philo *philo)
{
	int	fork;

	pthread_mutex_lock(&philo->fork);
	fork = philo->latch;
	if (fork == 0)
		philo->latch = 1;
	pthread_mutex_unlock(&philo->fork);
	return (fork);
}
/*
int	verif_right_fork(t_philo *philo)
{
	int		fork;
	t_philo	*next;

	pthread_mutex_lock(&philo->fork);
	fork = philo->latch;
	if (fork == 0)
		philo->latch = 1;
	pthread_mutex_unlock(&philo->fork);
	if (philo->n == philo->data->num_of_philo)
		next = &philo->data->philo[0];
	else
		next = &philo->data->philo[philo->n + 1];
	if (fork == 1)
	{
		pthread_mutex_lock(&next->fork);
		next->latch = 0;
		pthread_mutex_unlock(&next->fork);
		return (1);
	}
	return (0);
}
*/
int	verif_left_fork(t_philo *philo)
{
	int	fork;
	t_philo	*left;

	if (philo->n == philo->data->num_of_philo)
		left = &philo->data->philo[0];
	else
		left = &philo->data->philo[philo->n + 1];
	pthread_mutex_lock(&left->fork);
	fork = left->latch;
	if (fork == 0)
		left->latch = 1;
	pthread_mutex_unlock(&left->fork);
	if (fork == 1)
	{
		pthread_mutex_lock(&philo->fork);
		philo->latch = 0;
		pthread_mutex_unlock(&philo->fork);
	}
	return (fork);
}

int	verif_fork(t_philo *philo)
{
	int	right_fork;
	int	left_fork;
	t_philo	*left_philo;
	pthread_mutex_t	*philo_fork;

	if (philo->n == philo->data->num_of_philo)
	{
		left_philo = &philo->data->philo[0];
		philo_fork = &left_philo->fork;
	}
	else
	{
		left_philo = &philo->data->philo[philo->n + 1];
		philo_fork = &left_philo->fork;
	}
	pthread_mutex_lock(&philo->fork);
	right_fork = philo->latch;
	if (right_fork == 1)
		return (1);
	philo->latch = 1;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_lock(philo_fork);
	left_fork = left_philo->latch;
	if (left_fork == 0)
		left_philo->latch = 1;
	pthread_mutex_unlock(philo_fork);
	if (left_fork == 1)
	{
		pthread_mutex_lock(&philo->fork);
		philo->latch = 0;
		pthread_mutex_unlock(&philo->fork);
		return (1);
	}
	return (0);
}

void	safe_fork(t_philo *philo)
{
	t_philo	*next;

	if (philo->n == philo->data->num_of_philo)
		next = &philo->data->philo[0];
	else
		next = &philo->data->philo[philo->n + 1];
	pthread_mutex_lock(&next->fork);
	next->latch = 0;
	pthread_mutex_unlock(&next->fork);
	pthread_mutex_lock(&philo->fork);
	philo->latch = 0;
	pthread_mutex_unlock(&philo->fork);
}
