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
		if (!philo_think_initial(philo))
			return (NULL);
	increase_target_time(&philo->cycle_target_time,
		philo->initial_cycle_time_us);
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
