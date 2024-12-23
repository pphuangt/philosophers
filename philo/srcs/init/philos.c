/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:05:17 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/07 21:05:20 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, t_mutexes *mutexes,
				int *rules, t_timeval *s_time)
{
	static int	i = 0;

	philo->id = i + 1;
	philo->left = &mutexes->forks[i];
	philo->right = &mutexes->forks[(i + 1) % rules[NUMBER_OF_PHILO]];
	philo->state = ALIVE;
	philo->state_mutex = &mutexes->state_mutexes[i];
	philo->print_mutex = mutexes->print_mutex;
	philo->sync_mutex = mutexes->sync_mutex;
	philo->rules = rules;
	philo->s_time = s_time;
	memset(&philo->target_time, 0, sizeof(t_timeval));
	philo->start_time_us = set_start_time_us(rules, philo->id);
	philo->think_time_us = set_think_time_us(rules);
	philo->cycle_time_us = set_cycle_time_us(rules, philo);
	i++;
}

int	init_philos(t_philo **philos, t_mutexes *mutexes,
		int *rules, t_timeval *s_time)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * rules[NUMBER_OF_PHILO]);
	if (!*philos)
	{
		destroy_mutexes(mutexes, rules[NUMBER_OF_PHILO]);
		return (err_ret(MALLOC_ERR_MSG, MALLOC_ERROR));
	}
	memset(*philos, 0, sizeof(t_philo) * rules[NUMBER_OF_PHILO]);
	i = 0;
	while (i < rules[NUMBER_OF_PHILO])
		init_philo(&(*philos)[i++], mutexes, rules, s_time);
	return (SUCCESS);
}
