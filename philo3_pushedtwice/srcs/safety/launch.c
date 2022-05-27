/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:37:19 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 04:26:37 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
		pthread_mutex_destroy(&philo[i++].right.fork);
	pthread_mutex_destroy(&philo->data->dead);
	pthread_mutex_destroy(&philo->data->write);
}

void	ft_launch_philo(t_data *data, int i)
{
	pthread_mutex_init(&data->philo[i].right.fork, NULL);
	if (data->num_of_philo == 1)
		data->philo[i].left = NULL;
	else if (i == data->num_of_philo - 1)
		data->philo[i].left = &data->philo[0].right;
	else
		data->philo[i].left = &data->philo[i + 1].right;
	data->philo[i].right.index = i + 1;
	data->philo[i].right.status = 0;
	data->philo[i].n = i + 1;
	data->philo[i].meal = 0;
	data->philo[i].last_eat = ft_get_time();
	data->philo[i].data = data;
}

void	ft_launch(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = ft_get_time();
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->dead, NULL);
	while (i < data->num_of_philo)
		ft_launch_philo(data, i++);
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &safety, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
		pthread_join(data->philo[i++].thread, NULL);
	ft_free(data->philo);
}
