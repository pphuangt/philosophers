/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:30:54 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 10:30:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_forks(t_philo *philo, pthread_mutex_t **forks)
{
	if (philo->id & 1)
	{
		forks[0] = philo->left;
		forks[1] = philo->right;
	}
	else
	{
		forks[0] = philo->right;
		forks[1] = philo->left;
	}
}

int	take_forks(t_philo *philo, pthread_mutex_t **forks)
{
	pthread_mutex_lock(forks[0]);
	if (print_if_alive(philo, "%d %d has taken a fork\n") != SUCCESS)
	{
		pthread_mutex_unlock(forks[0]);
		return (-1);
	}
	pthread_mutex_lock(forks[1]);
	if (print_if_alive(philo, "%d %d has taken a fork\n") != SUCCESS)
	{
		release_forks(forks);
		return (-1);
	}
	return (SUCCESS);
}

void	release_forks(pthread_mutex_t **forks)
{
	pthread_mutex_unlock(forks[0]);
	pthread_mutex_unlock(forks[1]);
}
