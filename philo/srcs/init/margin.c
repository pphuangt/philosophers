#include "philo.h"

t_ull	get_initial_think_margin_us(int *rules)
{
	return (rules[TIME_TO_EAT] / 2 * 1000ULL);
}

t_ull	get_think_margin_us(void)
{
	return (DEATH_MARGIN_MS / 2 * 1000ULL);
}
