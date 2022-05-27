/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 06:22:08 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 06:57:43 by asanson          ###   ########.fr       */
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
	if (safe_forks(philo, philo->left, &philo->right) == 0)
		return ;
	print_philo(philo, philo->n, "has taken a fork");
	print_philo(philo, philo->n, "has yaken a fork");
	check_life(philo);
	if (check_end(philo) == 0)
		philo->last_eat = ft_get_time();
	philo->meal++;
	print_philo(philo, philo->n, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	safe_unlock_forks(philo);
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
