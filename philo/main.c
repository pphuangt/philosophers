#include "philo.h"

static t_args	thread_arg_init(t_philo *philo, t_timeval s_time,
					int *limits, int *stop)
{
	t_args	ret;

	ret.philo = philo;
	ret.s_time = s_time;
	ret.limits = limits;
	ret.stop = stop;
	return (ret);
}

static t_thread	*threads_create(t_philo *philos, int *limits)
{
	t_thread	*threads;
	t_timeval	s_time;
	int			stop;
	int			number_of_philo;
	int			i;

	number_of_philo = limits[NUMBER_OF_PHILO];
	if (gettimeofday(&s_time, NULL) != 0)
		return (err_ret_pointer("gettimeofday", (t_thread *)NULL));
	threads = malloc(sizeof(*threads) * number_of_philo);
	if (!threads)
		return (err_ret_pointer("malloc", (t_thread *)NULL));
	stop = 0;
	i = -1;
	while (++i < number_of_philo)
	{
		threads[i].args = thread_arg_init(&philos[i], s_time, limits, &stop);
		if (pthread_create(&threads[i].tid, NULL,
				thread_process, &threads[i].args) != 0)
		{
			free(threads);
			return (err_ret_pointer("pthread_create", (t_thread *)NULL));
		}
	}
	return (threads);
}

static int	threads_join(t_thread *threads, int number_of_philo)
{
	int	i;

	i = 0;
	while (i < number_of_philo)
	{
		if (pthread_join(threads[i++].tid, NULL) != 0)
			return (err_ret_int("pthread_join", SYSTEM_ERROR));
	}
	return (SUCCESS);
}

static int	philosophers(int *limits)
{
	t_thread	*threads;
	t_philo		*philos;
	int			exit_code;

	exit_code = SYSTEM_ERROR;
	philos = philos_create(limits[NUMBER_OF_PHILO]);
	if (!philos)
		return (exit_code);
	threads = threads_create(philos, limits);
	if (!threads)
	{
		philos_clear(philos, NULL);
		return (exit_code);
	}
	if (threads_join(threads, limits[NUMBER_OF_PHILO]) == SUCCESS)
		exit_code = SUCCESS;
	philos_clear(philos, NULL);
	free(threads);
	return (exit_code);
}

int	main(int argc, char **argv)
{
	int	limits[MAX_ARGUMENT];
	int	i;

	if (argc != MAX_ARGUMENT && argc != MAX_ARGUMENT + 1)
		return (err_ret_int(INVALID_ARGUMENT, GENERAL_ERROR));
	limits[MAX_ARGUMENT - 1] = -1;
	i = 0;
	while (argv[++i])
	{
		limits[i - 1] = ft_atoi(argv[i]);
		if (limits[i - 1] < 0)
			return (err_ret_int(NEGATIVE_ARGUMENT, GENERAL_ERROR));
	}
	return (philosophers(limits));
}
