/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:37:29 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 04:24:35 by asanson          ###   ########.fr       */
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

void	safe_meal(t_philo *philo)
{
	if (verif_fork(philo) == 1)
		return ;
//	if (verif_left_fork(philo) == 1)
//		return ;
	print_philo(philo, philo->n, "has taken a fork");
	print_philo(philo, philo->n, "has taken a fork");
	check_life(philo);
	if (check_end(philo) == 0)
		philo->last_eat = ft_get_time();
	print_philo(philo, philo->n, "is eating");
	philo->meal++;
	ft_usleep(philo->data->time_to_eat, philo);
	safe_fork(philo);
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
