/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:00:47 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 14:01:07 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	if (philo->state & (DEAD | STOPPED))
	{
		philo->state |= CONFIRMED;
		pthread_mutex_unlock(philo->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->state_mutex);
	philo->timestamp_ms = get_elapsed_time_ms(philo->s_time);
	if ((philo->timestamp_ms - philo->meal_timestamp_ms)
		>= (t_ull)philo->rules[TIME_TO_DIE])
	{
		pthread_mutex_lock(philo->state_mutex);
		philo->state |= (DEAD | CONFIRMED);
		pthread_mutex_unlock(philo->state_mutex);
		return (0);
	}
	return (1);
}
