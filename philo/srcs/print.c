/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 07:28:09 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/12 07:28:10 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(philo->print_mutex);
	philo->timestamp_ms = get_elapsed_time_ms(philo->s_time);
	printf(msg, philo->timestamp_ms, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

int	print_if_alive(t_philo *philo, const char *msg)
{
	if (!is_alive(philo))
		return (-1);
	print_msg(philo, msg);
	return (SUCCESS);
}
