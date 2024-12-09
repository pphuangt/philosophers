#include "philo.h"

static void	set_forks(t_philo *philo, pthread_mutext_t **forks)
{
	if (philo->id & 1)
	{
		forks[0] = philo->left;
		forks[1] = philo->right;
	}
	else
	{
		forks[0] = philo->right;
		forks[1] = philo->left;
	}
}

void	*philosopher(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*forks[2];

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->sync_mutex);
	pthread_mutex_unlock(philo->sync_mutex);
	set_forks(philo, forks);
	while (42)
	{
		if (eating(philo, forks))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}
