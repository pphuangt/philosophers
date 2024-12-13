/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:00:41 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 14:00:42 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline __attribute__((always_inline))
void	busy_wait(t_ull us, t_timeval *s_usleep)
{
	while (get_elapsed_time_us(s_usleep) < us)
		;
}

static inline __attribute__((always_inline))
t_ull	usleep_return(unsigned int us, t_timeval *s_usleep)
{
	usleep(us);
	return (get_elapsed_time_us(s_usleep));
}

int	usleep_while_alive_precise(t_ull us, t_philo *philo)
{
	t_timeval	s_usleep;
	t_ull		slept_time_us;

	gettimeofday(&s_usleep, NULL);
	slept_time_us = 0;
	while (slept_time_us + USLEEP_SHORT_THRESHOLD_US < us)
	{
		if (!is_alive(philo))
			return (-1);
		slept_time_us = usleep_return(USLEEP_LONG_US, &s_usleep);
	}
	while (slept_time_us + BUSY_WAIT_THRESHOLD_US < us)
		slept_time_us = usleep_return(USLEEP_SHORT_US, &s_usleep);
	if (slept_time_us < us && is_alive(philo))
		busy_wait(us, &s_usleep);
	return (SUCCESS);
}
