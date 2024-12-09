#ifndef DEFINES_H
# define DEFINES_H

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

typedef enum e_state
{
	ALIVE			=		0b0000,
	FULL			=		0b0001,
	DEAD			=		0b0010,
	STOPPED			=		0b0100,
	CONFIRMED		=		0b1000
}	t_state;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state_mutexes;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*sync_mutex;
}	t_mutexes;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_state			state;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*state_mutex;
	pthread_mutex_t	*sync_mutex;
	pthread_mutex_t	*print_mutex;
	int				*rules;
	t_timeval		*s_time;
}	t_philo;

#endif