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
void	set_forks(t_philo *philo, pthread_mutex_t **forks);
int		take_forks(t_philo *philo, pthread_mutex_t **forks);
void	release_forks(pthread_mutex_t **forks);
void	monitor(t_philo *philos, int *rules);
void	broadcast(t_philo *philos, t_state state, int num_of_philos);
void	print_death(t_philo *philos, int num_of_philos, int dead_philo);
void	print_msg(t_philo *philo, const char *msg);
int		is_alive(t_philo *philo);
int		print_if_alive(t_philo *philo, const char *msg);
t_ull	set_start_time_us(int *rules, int id);
t_ull	set_think_time_us(int *rules);
t_ull	set_cycle_time_us(int *rules, t_philo *philo);
t_ull	to_us(t_timeval *time);
t_ull	get_elapsed_time_ms(t_timeval *s_time);
t_ull	get_elapsed_time_us(t_timeval *s_time);
t_ull	get_remaining_time_us(t_timeval *target_time);
void	increase_target_time(t_timeval *target_time, t_ull increase_us);
int		usleep_while_alive_precise(t_ull us, t_philo *philo);

#endif
