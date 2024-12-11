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

void	print_die(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%llu %d died\n", get_elapsed_time_ms(philo->s_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

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
	philo->latest_timestamp_ms = get_elapsed_time_ms(philo->s_time);
	if ((philo->latest_timestamp_ms - philo->last_meal_timestamp_ms)
		>= (t_ull)philo->rules[TIME_TO_DIE])
	{
		pthread_mutex_lock(philo->state_mutex);
		philo->state |= (DEAD | CONFIRMED);
		print_die(philo);
		pthread_mutex_unlock(philo->state_mutex);
		return (0);
	}
	return (1);
}
