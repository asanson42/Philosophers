/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:37:01 by asanson           #+#    #+#             */
/*   Updated: 2022/05/19 02:42:16 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_av(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+' || av[i][j] == '-')
			i++;
		while (av[i][j])
		{
			if (!(av[i][j] >= 48 && av[i][j] <= 57))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_init(t_data *data)
{
	if (data->num_of_philo <= 0)
		printf("Error: No Philosophers around the table.\n");
	else if (data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		printf("Error: Time.\n");
	else
		return (1);
	return (0);
}

int	parser(t_data *data, char **av, int ac)
{
	if (ft_check_av(av, ac) == 0)
		return (0);
	data->num_of_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->num_of_meal = ft_atoi(av[4]);
	else
		data->num_of_meal = -1;
	data->died = 0;
	if (ft_check_init(data) == 0)
		return (0);
	return (1);
}
