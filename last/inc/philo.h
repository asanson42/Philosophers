/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 05:55:17 by asanson           #+#    #+#             */
/*   Updated: 2022/05/27 06:52:31 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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

//PARSER
int					ft_atoi(char *str);
int					ft_check_av(char **av, int ac);
int					ft_check_init(t_data *data);
int					parser(t_data *data, char **av, int ac);

//UTILS
long int			ft_get_time(void);
int					check_end(t_philo *philo);
void				print_philo(t_philo *philo, int n, char *str);
void				check_life(t_philo *philo);
void				ft_usleep(long int ms, t_philo *philo);

//SAFE LAUNCH
void				ft_free(t_philo *philo);
void				ft_launch_philo(t_data *data, int i);
void				ft_launch(t_data *data);

//SAFETY
void				unlock_one_fork(t_fork *fork);
void				safe_unlock_forks(t_philo *philo);
int					safe_take(t_fork *fork);
int					safe_forks(t_philo *philo, t_fork *left, t_fork *right);
void				safe_sleep(t_philo *philo);
void				safe_meal(t_philo *philo);
void				*safety(void *arg);

#endif
