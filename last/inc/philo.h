#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_locktype
{
	LOCK = 0,
	UNLOCK = 1
}		t_locktype;

typedef struct	s_fork
{
	int				index;
	int				status;
	pthread_mutex_t	lock;
}		t_fork;

typedef struct	s_philo
{
	int				n;
	t_fork			*left;
	t_fork			*right;
	long int		start_time;
	long int		last_meal;
	int				meals;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_p
}

#endif
