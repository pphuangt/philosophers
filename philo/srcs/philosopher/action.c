/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:30:57 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 10:30:59 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo, pthread_mutex_t **forks)
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

int	sleeping(t_philo *philo)
{
	if (print_if_alive(philo, "%d %d is sleeping\n") != SUCCESS)
		return (-1);
	if (usleep_while_alive_precise(philo->rules[TIME_TO_SLEEP] * 1000ULL,
							philo) != SUCCESS)
		return (-1);
	return (SUCCESS);
}

int	thinking(t_philo *philo)
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

int	thinking_initial(t_philo *philo)
{
	if (print_if_alive(philo, "%d %d is thinking\n") != SUCCESS)
		return (-1);
	increase_target_time(&philo->cycle_target_time,
				philo->initial_think_time_us);
	if (usleep_while_alive_precise_target(&philo->cycle_target_time, philo)
			!= SUCCESS)
		return (-1);
	return (SUCCESS);
}
