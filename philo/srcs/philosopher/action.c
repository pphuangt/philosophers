#include "philo.h"

int	eating(t_philo *philo, pthread_mutex_t **forks)
{
	if (take_forks(philo, forks) != SUCCESS)
		return (-1);
	if (print_if_alive(philo, "eating") != SUCCESS)
	{
		release_forks(forks);
		return (-1);
	}
	// update last meal timestamp
	// usleep
	release_forks(forks);
	// check eat goal
	return (SUCCESS);
}

int	sleeping()
{
}

int	thinking()
{
}
