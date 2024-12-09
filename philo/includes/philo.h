/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:58:40 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/07 19:58:42 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "defines.h"
# include "utils.h"

int		init_rules(int *rules, int argc, char **argv);
int		init_mutexes(t_mutexes *mutexes, int number_of_philo);
void	destroy_mutexes(t_mutexes *mutexes, int count);
int		init_philos(t_philo **philos, t_mutexes *mutexes,
			int *rules, t_timeval *s_time);
int		init_threads(t_philo *philos, t_mutexes *mutexes,
			int *rules, t_timeval *s_time);
void	join_threads(t_philo *philos, int count);
void	*philosopher(void *arg);
void	monitor(t_philo *philos, int *rules);

#endif
