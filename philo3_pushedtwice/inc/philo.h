/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 02:36:35 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 03:56:36 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# include "./../libft/libft.h"

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				index;
	int				status;
	pthread_mutex_t	fork;
}		t_fork;

typedef struct s_philo
{
	int				n;
	int				meal;
	long int		last_eat;
	pthread_t		thread;
	t_fork			right;
	t_fork			*left;
	t_data			*data;
}			t_philo;

struct	s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meal;
	int				died;
	long int		t_start;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	t_philo			*philo;
};

// PARSER
int				ft_check_av(char **av, int ac);
int				ft_check_init(t_data *data);
int				parser(t_data *data, char **av, int ac);

// UTILS
long int		ft_get_time(void);
int				check_end(t_philo *philo);
void			print_philo(t_philo *philo, int n, char *str);
void			check_life(t_philo *philo);
void			ft_usleep(long int ms, t_philo *philo);

// SAFETY

int				verif_fork(t_philo *philo);

int				verif_right_fork(t_philo *philo);
int				verif_left_fork(t_philo *philo);
void			safe_fork(t_philo *philo);
void			safe_sleep(t_philo *philo);
void			safe_meal(t_philo *philo);
void			*safety(void *arg);

// LAUNCH
void			ft_free(t_philo *philo);
void			ft_launch_philo(t_data *data, int i);
void			ft_launch(t_data *data);

#endif
