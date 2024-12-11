/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:00:19 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 14:00:20 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_ull	calc_think_block_us(int *rules)
{
	if (rules[NUMBER_OF_PHILO] < 2)
		return (rules[TIME_TO_DIE] * 1000ULL);
	else
		return (2ULL * rules[TIME_TO_EAT] * 1000
			/ (rules[NUMBER_OF_PHILO] & ~1));
}

t_ull	calc_initial_think_time_us(int *rules, int id)
{
	int	block_amount;

	if (rules[NUMBER_OF_PHILO] < 2)
		return (rules[TIME_TO_DIE] * 1000ULL);
	else if (rules[NUMBER_OF_PHILO] & 1)
	{
		block_amount = id / 2;
		if (!(id & 1))
			block_amount += rules[NUMBER_OF_PHILO] / 2;
		return (calc_think_block_us(rules) * block_amount);
	}
	else
	{
		if (id & 1)
			return (0);
		return (rules[TIME_TO_EAT] * 1000ULL - get_initial_think_margin_us(rules));
	}
}

t_ull	calc_think_time_us(int *rules)
{
	long long	think_time_us;

	think_time_us = (rules[TIME_TO_EAT] - rules[TIME_TO_SLEEP]) * 1000LL
		- (long long)get_think_margin_us();
	if (rules[NUMBER_OF_PHILO] & 1)
		think_time_us += (long long)calc_think_block_us(rules);
	if (think_time_us > 0)
		return (think_time_us);
	return (0);
}

t_ull	calc_initial_cycle_time_us(int *rules, t_philo *philo)
{
	t_ull	initial_cycle_time_us;

	initial_cycle_time_us = ((t_ull)rules[TIME_TO_EAT] + rules[TIME_TO_SLEEP])
		* 1000 + philo->think_time_us;
	if (!(rules[NUMBER_OF_PHILO] & 1) && !(philo->id & 1))
		initial_cycle_time_us += get_initial_think_margin_us(rules);
	return (initial_cycle_time_us);
}

t_ull	calc_cycle_time_us(int *rules, t_philo *philo)
{
	t_ull	cycle_time_us;

	cycle_time_us = ((t_ull)rules[TIME_TO_EAT]
			+ rules[TIME_TO_SLEEP]) * 1000 + philo->think_time_us;
	if (philo->think_time_us)
		cycle_time_us += get_think_margin_us();
	return (cycle_time_us);
}
