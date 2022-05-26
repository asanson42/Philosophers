/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:36:47 by asanson           #+#    #+#             */
/*   Updated: 2022/05/26 03:33:19 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong amount of arguments.\n");
		return (0);
	}
	parser(&data, av + 1, ac - 1);
	if (data.num_of_philo <= 0)
		return (0);
	data.philo = malloc(sizeof(t_philo) * (data.num_of_philo));
	if (!data.philo)
		return (0);
	ft_launch(&data);
	free(data.philo);
	return (0);
}
