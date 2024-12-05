#include "philo.h"

void	forks_clear(t_fork **forks)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (forks[i])
	{
		if (forks[i]->mutex_initialized)
			pthread_mutex_destroy(&forks[i]->mutex);
		free(forks[i++]);
	}
	free(forks);
}

void	philos_clear(t_philo *philos, t_fork **forks)
{
	static t_fork	**s_forks = NULL;

	if (forks)
	{
		s_forks = forks;
		return ;
	}
	forks_clear(s_forks);
	s_forks = NULL;
	free(philos);
}
