/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:37:29 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 05:28:34 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_sleep(t_philo *philo)
{
	print_philo(philo, philo->n, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	print_philo(philo, philo->n, "is thinking");
	ft_usleep(1, philo);
}

void	print_forkstate(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->data->write);
	if (state == 1)
		printf("before eat:\n");
	else if (state == 2)
		printf("after take fork:\n");
	else
		printf("after leave:\n");
	printf("philo %d right fork: %d\n", philo->n, philo->right.status);
	printf("philo %d left fork: %d\n\n", philo->n, philo->left->status);
	pthread_mutex_unlock(&philo->data->write);
}

void	unlock_one_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	fork->status = 0;
	pthread_mutex_unlock(&fork->fork);
}

void	unlock_forks(t_philo *philo)
{
	unlock_one_fork(philo->left);
	unlock_one_fork(&philo->right);
}

int	ft_take_one_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->fork);
	if (fork->status == 0)
	{
		fork->status = 1;
		pthread_mutex_unlock(&fork->fork);
		return (0);
	}
	pthread_mutex_unlock(&fork->fork);
	return (1);
}

int	check_forks(t_philo *philo, t_fork *left, t_fork *right)
{
	if (ft_take_one_fork(left))
	{
		usleep(500);
		return (1);
	}
	if (ft_take_one_fork(right))
	{
		unlock_one_fork(left);
		usleep(500);
		return (1);
	}
	return (0);
}

void	safe_meal(t_philo *philo)
{
//	print_forkstate(philo, 1);
	if (check_forks(philo, philo->left, &philo->right))
		return ;
//	print_forkstate(philo, 2);
//	if (verif_left_fork(philo) == 1)
//		return ;
	print_philo(philo, philo->n, "has taken a fork");
	print_philo(philo, philo->n, "has taken a fork");
	check_life(philo);
	if (check_end(philo) == 0)
		philo->last_eat = ft_get_time();
	philo->meal++;
	print_philo(philo, philo->n, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
//	print_philo(philo, philo->n, "ate well");
	//safe_fork(philo);
	unlock_forks(philo);
//	print_philo(philo, philo->n, "safe well");
//	print_forkstate(philo, 3);
	safe_sleep(philo);
}

void	*safety(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_of_philo == 1)
	{
		pthread_mutex_lock(&philo->right.fork);
		print_philo(philo, philo->n, "has taken a fork");
		ft_usleep(philo->data->time_to_die, philo);
		print_philo(philo, philo->n, "died");
		pthread_mutex_unlock(&philo->right.fork);
		return (NULL);
	}
	if (philo->n % 2 != 0)
		usleep(1);
	if (philo->data->num_of_meal >= 0)
		while (philo->meal < philo->data->num_of_meal && check_end(philo) == 0)
			safe_meal(philo);
	else
		while (check_end(philo) == 0)
			safe_meal(philo);
	return (NULL);
}
