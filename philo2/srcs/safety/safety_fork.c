#include "philo.h"

int	verif_left_fork(t_philo *philo)
{
	int		fork;
	t_philo *next;

	if (philo->n == philo->data->num_of_philo - 1)
		next = &philo->data->philo[0];
	else
		next = &philo->data->philo[philo->n + 1];
	pthread_mutex_lock(philo->left_fork);
	fork = next->fork;
	if (fork == 0)
		next->fork = 1;
	pthread_mutex_unlock(philo->left_fork);
	return (fork);
}

int	verif_right_fork(t_philo *philo)
{
	int		fork;
	t_philo *next;

	pthread_mutex_lock(&philo->right_fork);
	fork = philo->fork;
	if (fork == 0)
		philo->fork = 1;
	pthread_mutex_unlock(&philo->right_fork);
	if (philo->n == philo->data->num_of_philo - 1)
		next = &philo->data->philo[0];
	else
		next = &philo->data->philo[philo->n + 1];
	if (fork == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		next->fork = 0;
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	safe_fork(t_philo *philo)
{
	t_philo	*next;

	if (philo->n == philo->data->num_of_philo - 1)
		next = &philo->data->philo[0];
	else
		next = &philo->data->philo[philo->n + 1];
	pthread_mutex_lock(&philo->right_fork);
	philo->fork = 0;
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	next->fork = 0;
	pthread_mutex_unlock(philo->left_fork);
}
