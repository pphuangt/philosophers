/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:28:32 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 10:28:34 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline __attribute__((always_inline))
t_state	monitor_cycle(t_philo *philos, int num_of_philos)
{
	int		i;
	t_state	state;

	i = 0;
	state = ~0;
	while (i < num_of_philos)
	{
		state |= DEAD;
		pthread_mutex_lock(philos[i].state_mutex);
		state &= philos[i].state;
		pthread_mutex_unlock(philos[i].state_mutex);
		if (state & DEAD)
		{
			broadcast(philos, DEAD, num_of_philos);
			print_death(philos, num_of_philos, i);
			break ;
		}
		i++;
	}
	return (state);
}

void	monitor(t_philo *philos, int *rules)
{
	t_state	state;

	while (42)
	{
		usleep(MONITOR_INTERVAL_US);
		state = monitor_cycle(philos, rules[NUMBER_OF_PHILO]);
		if (state & DEAD)
			return ;
		else if (state & FULL)
		{
			broadcast(philos, STOPPED, rules[NUMBER_OF_PHILO]);
			return ;
		}
	}
}
