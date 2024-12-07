#include "philo.h"

int	main(int argc, char **argv)
{
	//t_philo		*philos;
	t_mutexes	mutexes;
	int			rules[NUMBER_OF_RULE];
	//t_timeval	start_time;

	if (init_rules(rules, argc, argv) != SUCCESS)
		return (INPUT_ERROR);
	if (!rules[NUMBER_OF_PHILO] || !rules[NUMBER_OF_EAT_GOAL])
		return (SUCCESS);
	if (init_mutexes(&mutexes, rules[NUMBER_OF_PHILO]) != SUCCESS)
		return (MUTEX_ERROR);
	printf("%d %d %d %d %d\n", rules[0], rules[1], rules[2], rules[3], rules[4]);
	destroy_mutexes(&mutexes, rules[NUMBER_OF_PHILO]);
	return (0);
}
