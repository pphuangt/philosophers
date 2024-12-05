#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define NUMBER_OF_PHILO	0
# define TIME_TO_DIE		1
# define TIME_TO_EAT		2
# define TIME_TO_SLEEP		3
# define NUMBER_MUST_EAT	4
# define MAX_ARGUMENT		5
# define SUCCESS			0
# define SYSTEM_ERROR		1
# define GENERAL_ERROR		2
# define INVALID_ARGUMENT	"./philo {number} {number} {number} {number} [number]"
# define NEGATIVE_ARGUMENT	"The value of number must be nonnegative (possible overflow)"

typedef struct timeval t_timeval;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				mutex_initialized;
}	t_fork;

typedef struct s_philo {
	int			id;
	t_fork		*left;
	t_fork		*right;
}	t_philo;

typedef struct s_args {
	t_philo		*philo;
	t_timeval	s_time;
	int			*limits;
	int			*stop;
}	t_args;

typedef struct s_thread {
	pthread_t	tid;
	t_args		args;
}	t_thread;

int		ft_atoi(const char *s);
t_philo	*philos_create(int number_of_philo);
void	*thread_process(void *args);
void	philos_clear(t_philo *philos, t_fork **forks);
void	forks_clear(t_fork **forks);
int		err_ret_int(char *s, int return_code);
void	*err_ret_pointer(char *s, void *return_pointer);

# endif
