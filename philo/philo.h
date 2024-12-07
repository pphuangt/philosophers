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

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define NUMBER_OF_RULE 5
# define INVALID_ARG_ERR_MSG "Error: arguments must be a number and positive"
# define ARG_TO_LARGE_ERR_MSG "Error: arguments is too large (overflow)"
# define ARG_NUM_ERR_MSG "Error: Wrong number of arguments"
# define MALLOC_ERR_MSG "Error: malloc function"
# define MUTEX_ERR_MSG "Error: pthread_mutex_init function"
# define THREAD_ERR_MSG "Error: pthread_create function"
# define GETTIME_ERR_MSG "Error: gettimeofday function"

typedef struct timeval	t_timeval;

enum e_exit_codes
{
	SUCCESS,
	INPUT_ERROR,
	MALLOC_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
	GETTIME_ERROR,
};

enum e_rules
{
	NUMBER_OF_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_EAT_GOAL
};

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*states;
	pthread_mutex_t	*print;
	pthread_mutex_t	*sync;
}	t_mutexes;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*state;
	pthread_mutex_t	*print;
	pthread_mutex_t	*sync;
	int				*rules;
	t_timeval		*s_time;
}	t_philo;

/*    philos    */
int		init_philos(t_philo **philos, t_mutexes *mutexes,
			int *rules, t_timeval *s_time);
/*    mutexes    */
int		init_mutexes(t_mutexes *mutexes, int number_of_philo);
void	destroy_mutexes(t_mutexes *mutexes, int count);
/*    rules    */
int		init_rules(int *rules, int argc, char **argv);
/*    error    */
int		err_ret_int(char *s, int return_code);
void	*err_ret_pointer(char *s, void *return_pointer);
/*    utils    */
int		ft_isdigit(int c);
int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);

#endif
