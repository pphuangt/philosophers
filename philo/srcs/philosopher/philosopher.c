/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:30:50 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 10:30:51 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *philo, pthread_mutex_t **forks)
{
	if (take_forks(philo, forks) != SUCCESS)
		return (-1);
	if (print_if_alive(philo, "%d %d is eating\n") != SUCCESS)
	{
		release_forks(forks);
		return (-1);
	}
	philo->last_meal_timestamp_ms = philo->latest_timestamp_ms;
	if (usleep_while_alive_precise(philo->rules[TIME_TO_EAT] * 1000ULL, philo)
		!= SUCCESS)
	{
		release_forks(forks);
		return (-1);
	}
	release_forks(forks);
	philo->meals_eaten++;
	if (philo->rules[NUMBER_OF_EAT_GOAL] > 0 && philo->meals_eaten
		== philo->rules[NUMBER_OF_EAT_GOAL])
	{
		pthread_mutex_lock(philo->state_mutex);
		philo->state |= FULL;
		pthread_mutex_unlock(philo->state_mutex);
	}
	return (SUCCESS);
}

static int	sleeping(t_philo *philo)
{
	if (print_if_alive(philo, "%d %d is sleeping\n") != SUCCESS)
		return (-1);
	if (usleep_while_alive_precise(philo->rules[TIME_TO_SLEEP] * 1000ULL,
			philo) != SUCCESS)
		return (-1);
	return (SUCCESS);
}

static int	thinking(t_philo *philo)
{
	if (print_if_alive(philo, "%d %d is thinking\n") != SUCCESS)
		return (-1);
	if (philo->think_time_us)
	{
		if (usleep_while_alive_precise_target(&philo->cycle_target_time,
				philo) != SUCCESS)
			return (-1);
		increase_target_time(&philo->cycle_target_time, philo->cycle_time_us);
	}
	return (SUCCESS);
}

static int	wait_start_time(t_philo *philo)
{
	if (!is_alive(philo))
		return (-1);
	increase_target_time(&philo->cycle_target_time,
		philo->start_time_us);
	if (usleep_while_alive_precise_target(&philo->cycle_target_time, philo)
		!= SUCCESS)
		return (-1);
	return (SUCCESS);
}

void	*philosopher(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*forks[2];

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->sync_mutex);
	pthread_mutex_unlock(philo->sync_mutex);
	set_forks(philo, forks);
	timeradd(&philo->cycle_target_time, philo->s_time,
		&philo->cycle_target_time);
	if (philo->start_time_us)
		if (wait_start_time(philo) != SUCCESS)
			return (NULL);
	increase_target_time(&philo->cycle_target_time,
		philo->initial_cycle_time_us);
	while (42)
	{
		if (eating(philo, forks) != SUCCESS)
			break ;
		if (sleeping(philo) != SUCCESS)
			break ;
		if (thinking(philo) != SUCCESS)
			break ;
	}
	return (NULL);
}
