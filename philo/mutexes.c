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
	if (mutexes->states)
		iter_destroy_mutexes(&mutexes->states, count);
	if (mutexes->sync)
		iter_destroy_mutexes(&mutexes->sync, 1);
	if (mutexes->print)
		iter_destroy_mutexes(&mutexes->print, 1);
}

static int	iter_init_mutexes(pthread_mutex_t **mutexes_member, int count)
{
	int	i;

	*mutexes_member = malloc(count * sizeof(pthread_mutex_t));
	if (!*mutexes_member)
	{
		ft_putendl_fd(MALLOC_ERR_MSG, STDERR_FILENO);
		return (MALLOC_ERROR);
	}
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(*mutexes_member)[i], NULL) != 0)
		{
			iter_destroy_mutexes(mutexes_member, i);
			ft_putendl_fd(MUTEX_ERR_MSG, STDERR_FILENO);
			return (MUTEX_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_mutexes(t_mutexes *mutexes, int count)
{
	int	exit_code;

	memset(mutexes, 0, sizeof(t_mutexes) * count);
	exit_code = iter_init_mutexes(&mutexes->forks, count);
	if (exit_code == SUCCESS)
		exit_code = iter_init_mutexes(&mutexes->states, count);
	if (exit_code == SUCCESS)
		exit_code = iter_init_mutexes(&mutexes->sync, 1);
	if (exit_code == SUCCESS)
		exit_code = iter_init_mutexes(&mutexes->print, 1);
	if (exit_code != SUCCESS)
		destroy_mutexes(mutexes, count);
	return (exit_code);
}
