/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:37:43 by asanson           #+#    #+#             */
/*   Updated: 2022/05/25 03:27:56 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (0);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

int	check_end(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->data->dead);
	i = philo->data->died;
	pthread_mutex_unlock(&philo->data->dead);
	return (i);
}

void	print_philo(t_philo *philo, int n, char *str)
{
	pthread_mutex_lock(&philo->data->write);
	if (check_end(philo) == 0)
		printf("%ld %d %s\n", ft_get_time() - philo->data->t_start, n, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	check_life(t_philo *philo)
{
	if ((ft_get_time() - philo->last_eat) > philo->data->time_to_die)
	{
		print_philo(philo, philo->n, "died");
		pthread_mutex_lock(&philo->data->dead);
		philo->data->died = 1;
		pthread_mutex_unlock(&philo->data->dead);
	}
}

void	ft_usleep(long int ms, t_philo *philo)
{
	long int	time;

	time = ft_get_time();
	while (ft_get_time() - time < ms)
	{
		check_life(philo);
		if (check_end(philo) == 1)
			break ;
		usleep(100);
	}
}
