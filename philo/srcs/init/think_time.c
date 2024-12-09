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
		return (block_amount * rules[TIME_TO_EAT] * 2000ULL
			/ (rules[NUMBER_OF_PHILO] & ~1));
	}
	else
	{
		if (id & 1)
			return (0);
		return ((rules[TIME_TO_EAT] - rules[TIME_TO_EAT] / 2) * 1000ULL);
	}
}

t_ull	calc_think_time_us(int *rules)
{
	long long	think_time_us;

	think_time_us = (rules[TIME_TO_EAT] - rules[TIME_TO_SLEEP] - 5) * 1000LL;
	if (rules[NUMBER_OF_PHILO] & 1)
	{
		if (rules[NUMBER_OF_PHILO] < 2)
			think_time_us += rules[TIME_TO_DIE] * 1000LL;
		else
			think_time_us += rules[TIME_TO_EAT] * 1000LL
				/ (rules[NUMBER_OF_PHILO] & ~1);
	}
	if (think_time_us > 0)
		return (think_time_us);
	return (0);
}
