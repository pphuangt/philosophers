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

void	print_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("--------------------\n");
	printf("id: %d\n", philo->id);
	printf("initial_think_time_us: %llu\n", philo->initial_think_time_us);
	printf("think_timie_us: %llu\n", philo->think_time_us);
	printf("initial_cycle_time_us: %llu\n", philo->initial_cycle_time_us);
	printf("cycle_time_us: %llu\n", philo->cycle_time_us);
	printf("--------------------\n");
	pthread_mutex_unlock(philo->print_mutex);
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
	if (philo->initial_think_time_us)
		if (thinking_initial(philo) != SUCCESS)
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
