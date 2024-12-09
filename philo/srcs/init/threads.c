#include "philo.h"

void	join_threads(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_join(philos[i++].thread, NULL);
}

static int	create_philo_threads(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philos[i].thread, NULL, philosopher, &philos[i]) != 0)
		{
			//broadcast(philos, STOPPED, i);
			pthread_mutex_unlock(philos[i].sync_mutex);
			join_threads(philos, i);
			return (err_ret_int(THREAD_ERR_MSG, THREAD_ERROR));
		}
		i++;
	}
	return (SUCCESS);
}

int	init_threads(t_philo *philos, t_mutexes *mutexes,
			int *rules, t_timeval *s_time)
{
	pthread_mutex_lock(mutexes->sync_mutex);
	if (create_philo_threads(philos, rules[NUMBER_OF_PHILO]) != SUCCESS)
	{
		destroy_mutexes(mutexes, rules[NUMBER_OF_PHILO]);
		free(philos);
		return (THREAD_ERROR);
	}
	gettimeofday(s_time, NULL);
	pthread_mutex_unlock(mutexes->sync_mutex);
	return (SUCCESS);
}
