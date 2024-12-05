#include "philo.h"

static void	mutex_lock(int id, t_fork *left, t_fork *right)
{
	if (id % 2 == 0)
	{
		pthread_mutex_lock(&left->mutex);
		pthread_mutex_lock(&right->mutex);
	}
	else
	{
		pthread_mutex_lock(&right->mutex);
		pthread_mutex_lock(&left->mutex);
	}
}

static void	mutex_unlock(int id, t_fork *left, t_fork *right)
{
	if (id % 2 == 0)
	{
		pthread_mutex_unlock(&left->mutex);
		pthread_mutex_unlock(&right->mutex);
	}
	else
	{
		pthread_mutex_unlock(&right->mutex);
		pthread_mutex_unlock(&left->mutex);
	}
}

int	milliseconds(t_timeval start, t_timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000);
}

int	is_starve(t_args *thread_args, int strave, int time)
{
	if (strave > thread_args->limits[TIME_TO_DIE])
	{
		*(thread_args->stop) = 1;
		printf("%d %d died\n", time, thread_args->philo->id);
		return (1);
	}
	return (0);
}

int	eating(t_args *thread_args, t_timeval *die)
{
	t_timeval	cur;
	int			strave;
	int			time;

	if (*(thread_args->stop) == 1)
		return (-1);
	gettimeofday(&cur, NULL);
	strave = milliseconds(*die, cur);
	time = milliseconds(thread_args->s_time, cur);
	if (is_starve(thread_args, strave, time))
		return (-1);
	printf("%d %d is eating\n", time, thread_args->philo->id);
	gettimeofday(die, NULL);
	usleep(thread_args->limits[TIME_TO_EAT] * 1000);
	return (0);
}

int	sleeping(t_args *thread_args, t_timeval *die)
{
	t_timeval	cur;
	int			strave;
	int			time;

	if (*(thread_args->stop) == 1)
		return (-1);
	gettimeofday(&cur, NULL);
	strave = milliseconds(*die, cur);
	time = milliseconds(thread_args->s_time, cur);
	if (is_starve(thread_args, strave, time))
		return (-1);
	printf("%d %d is sleeping\n", time, thread_args->philo->id);
	usleep(thread_args->limits[TIME_TO_SLEEP] * 1000);
	return (0);
}

int	thinking(t_args *thread_args, t_timeval *die)
{
	t_timeval	cur;
	int			strave;
	int			time;

	if (*(thread_args->stop) == 1)
		return (-1);
	gettimeofday(&cur, NULL);
	strave = milliseconds(*die, cur);
	time = milliseconds(thread_args->s_time, cur);
	if (is_starve(thread_args, strave, time))
		return (-1);
	printf("%d %d is thinking\n", time, thread_args->philo->id);
	return (0);
}

void	*thread_process(void *args)
{
	t_args		*thread_args;
	t_philo		*philo;
	t_timeval	die;
	int			number_must_eat;
	int			i;

	thread_args = (t_args *)args;
	philo = thread_args->philo;
	die = thread_args->s_time;
	number_must_eat = thread_args->limits[NUMBER_MUST_EAT];
	i = 0;
	while (number_must_eat == -1 || i++ < number_must_eat)
	{
		mutex_lock(philo->id, philo->left, philo->right);
		if (eating(thread_args, &die) != 0)
		{
			mutex_unlock(philo->id, philo->left, philo->right);
			return (NULL);
		}
		mutex_unlock(philo->id, philo->left, philo->right);
		if (sleeping(thread_args, &die) != 0)
			return (NULL);
		if (thinking(thread_args, &die) != 0)
			return (NULL);
	}
	return (NULL);
}
