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
	if (print_if_alive(philo, "eating") != SUCCESS)
	{
		release_forks(forks);
		return (-1);
	}
	// update last meal timestamp
	// usleep
	release_forks(forks);
	// check eat goal
	return (SUCCESS);
}

int	sleeping()
{
}

int	thinking()
{
}

int	philo_think_initial(t_philo *philo)
{
	if (!print_if_alive(philo, "thinking"))
		return (0);
	increate_target_time(&philo->cycle_target_time,
		philo->initial_cycle_time_us);
	// if (!usleep_while_alive_precise_target)
	return (1);
}
