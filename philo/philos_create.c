#include "philo.h"

static t_fork	**forks_create(int number_of_philo)
{
	t_fork	**forks;
	int		i;

	forks = malloc(sizeof(*forks) * (number_of_philo + 1));
	if (!forks)
		return (err_ret_pointer("malloc", (t_fork **)NULL));
	memset(forks, 0, sizeof(*forks) * (number_of_philo + 1));
	i = 0;
	while (i < number_of_philo)
	{
		forks[i] = malloc(sizeof(**forks));
		if (!forks[i])
		{
			forks_clear(forks);
			return (err_ret_pointer("malloc", (t_fork **)NULL));
		}
		if (pthread_mutex_init(&forks[i]->mutex, NULL) != 0)
		{
			forks[i]->mutex_initialized = 0;
			forks_clear(forks);
			return (err_ret_pointer("pthread_mutex_init", (t_fork **)NULL));
		}
		forks[i++]->mutex_initialized = 1;
	}
	return (forks);
}

static void	philos_init(t_philo *philo, t_fork **forks, int number_of_philo)
{
	int			i;

	i = -1;
	while (++i < number_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].left = forks[i];
		philo[i].right = forks[(i + 1) % number_of_philo];
	}
}

t_philo	*philos_create(int number_of_philo)
{
	t_philo		*philos;
	t_fork		**forks;

	forks = forks_create(number_of_philo);
	if (!forks)
		return (NULL);
	philos = malloc(sizeof(*philos) * number_of_philo);
	if (!philos)
	{
		forks_clear(forks);
		return (err_ret_pointer("malloc", (t_philo *)NULL));
	}
	memset(philos, 0, sizeof(*philos) * number_of_philo);
	philos_clear(NULL, forks);
	philos_init(philos, forks, number_of_philo);
	return (philos);
}
