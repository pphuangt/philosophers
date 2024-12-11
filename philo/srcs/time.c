/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:01:24 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 14:01:25 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ull	to_us(t_timeval *time)
{
	return (time->tv_sec * 1000000 + time->tv_usec);
}

t_ull	get_elapsed_time_ms(t_timeval *s_time)
{
	t_timeval	current;
	t_timeval	result;

	gettimeofday(&current, NULL);
	timersub(&current, s_time, &result);
	return (result.tv_sec * 1000ULL + result.tv_usec / 1000);
}

t_ull	get_elapsed_time_us(t_timeval *s_time)
{
	t_timeval	current;
	t_timeval	result;

	gettimeofday(&current, NULL);
	timersub(&current, s_time, &result);
	return (to_us(&result));
}

t_ull	get_remaining_time_us(t_timeval *target_time)
{
	t_timeval	current;
	t_timeval	result;

	gettimeofday(&current, NULL);
	if (timercmp(&current, target_time, >))
		return (0);
	timersub(target_time, &current, &result);
	return (to_us(&result));
}

void	increase_target_time(t_timeval *target_time, t_ull increase_us)
{
	t_timeval	increase;

	increase.tv_sec = increase_us / 1000000;
	increase.tv_usec = increase_us % 1000000;
	timeradd(target_time, &increase, target_time);
}
