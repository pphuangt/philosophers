/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:58:33 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/07 19:58:34 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	iter_destroy_mutexes(pthread_mutex_t **mutexes_member, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_mutex_destroy(&(*mutexes_member)[i++]);
	free(*mutexes_member);
	*mutexes_member = NULL;
}

void	destroy_mutexes(t_mutexes *mutexes, int count)
{
	if (mutexes->forks)
		iter_destroy_mutexes(&mutexes->forks, count);
	if (mutexes->state_mutexes)
		iter_destroy_mutexes(&mutexes->state_mutexes, count);
	if (mutexes->sync_mutex)
		iter_destroy_mutexes(&mutexes->sync_mutex, 1);
	if (mutexes->print_mutex)
		iter_destroy_mutexes(&mutexes->print_mutex, 1);
}

static int	iter_init_mutexes(pthread_mutex_t **mutexes_member, int count)
{
	int	i;

	*mutexes_member = malloc(count * sizeof(pthread_mutex_t));
	if (!*mutexes_member)
		return (err_ret_int(MALLOC_ERR_MSG, MALLOC_ERROR));
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*mutexes_member)[i], NULL) != 0)
		{
			iter_destroy_mutexes(mutexes_member, i);
			return (err_ret_int(MUTEX_ERR_MSG, MUTEX_ERROR));
		}
		i++;
	}
	return (SUCCESS);
}

int	init_mutexes(t_mutexes *mutexes, int count)
{
	int	exit_code;

	memset(mutexes, 0, sizeof(t_mutexes));
	exit_code = iter_init_mutexes(&mutexes->forks, count);
	if (exit_code == SUCCESS)
		exit_code = iter_init_mutexes(&mutexes->state_mutexes, count);
	if (exit_code == SUCCESS)
		exit_code = iter_init_mutexes(&mutexes->sync_mutex, 1);
	if (exit_code == SUCCESS)
		exit_code = iter_init_mutexes(&mutexes->print_mutex, 1);
	if (exit_code != SUCCESS)
		destroy_mutexes(mutexes, count);
	return (exit_code);
}
