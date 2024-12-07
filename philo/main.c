/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:57:56 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/07 19:57:58 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_mutexes	mutexes;
	int			rules[NUMBER_OF_RULE];
	t_timeval	s_time;

	if (init_rules(rules, argc, argv) != SUCCESS)
		return (INPUT_ERROR);
	if (!rules[NUMBER_OF_PHILO] || !rules[NUMBER_OF_EAT_GOAL])
		return (SUCCESS);
	if (init_mutexes(&mutexes, rules[NUMBER_OF_PHILO]) != SUCCESS)
		return (MUTEX_ERROR);
	if (init_philos(&philos, &mutexes, rules, &s_time) != SUCCESS)
		return (MALLOC_ERROR);
	destroy_mutexes(&mutexes, rules[NUMBER_OF_PHILO]);
	return (0);
}
