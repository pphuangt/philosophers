/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:32:21 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/12 08:32:23 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_all_dead(t_philo *philos, int num_of_philos)
{
	t_state	state;
	int		i;

	while (42)
	{
		usleep(MONITOR_INTERVAL_US);
		i = 0;
		state = ~0;
		while (i < num_of_philos)
		{
			pthread_mutex_lock(philos[i].state_mutex);
			state &= philos[i].state;
			pthread_mutex_unlock(philos[i].state_mutex);
			i++;
		}
		if ((state & (DEAD | CONFIRMED)) == (DEAD | CONFIRMED))
			break ;
	}
}

void	print_death(t_philo *philos, int num_of_philos, int dead_philo)
{
	wait_all_dead(philos, num_of_philos);
	print_msg(&philos[dead_philo], "%d %d died\n");
}

void	broadcast(t_philo *philos, t_state state, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		pthread_mutex_lock(philos[i].state_mutex);
		philos[i].state |= state;
		pthread_mutex_unlock(philos[i].state_mutex);
		i++;
	}
}
