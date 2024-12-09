#include "philo.h"

int	take_forks(t_philo *philo, pthread_mutex_t **forks)
{
	pthread_mutex_lock(forks[0]);
	if (print_if_alive(philo, "take fork") != SUCCESS)
	{
		pthread_mutex_unlock(forks[0]);
		return (-1);
	}
	pthread_mutex_lock(forks[1]);
	if (print_if_alive(philo, "take fork") != SUCCESS)
	{
		pthread_mutex_unlock(forks[0]);
		pthread_mutex_unlock(forks[1]);
		return (-1);
	}
	return (SUCCESS);
}

void	release_forks(pthread_mutext_t **forks)
{
	pthread_mutex_unlock(forks[0]);
	pthread_mutex_unlock(forks[1]);
}
