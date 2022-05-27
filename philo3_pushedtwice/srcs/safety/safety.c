/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:37:29 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 04:40:13 by asanson          ###   ########.fr       */
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

void	safe_meal(t_philo *philo)
{
	print_forkstate(philo, 1);
	if (verif_fork(philo) == 1)
		return ;
	print_forkstate(philo, 2);
//	if (verif_left_fork(philo) == 1)
//		return ;
	print_philo(philo, philo->n, "has taken a fork");
	print_philo(philo, philo->n, "has taken a fork");
	check_life(philo);
	if (check_end(philo) == 0)
		philo->last_eat = ft_get_time();
	print_philo(philo, philo->n, "is eating");
	philo->meal++;
	printf("1");
	ft_usleep(philo->data->time_to_eat, philo);
	printf("2");
	safe_fork(philo);
	print_forkstate(philo, 3);
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
