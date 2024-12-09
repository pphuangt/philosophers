/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:58:18 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/07 19:58:20 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_overflow_int(const char *nptr)
{
	int		i;
	char	*int_max;
	int		int_max_len;
	int		num_len;

	i = 0;
	int_max = "2147483647";
	int_max_len = ft_strlen(int_max);
	while (nptr[i] == '0')
		i++;
	num_len = 0;
	while (ft_isdigit(nptr[i + num_len]))
		num_len++;
	if ((num_len == int_max_len && ft_strncmp(&nptr[i], int_max, num_len) > 0)
		|| num_len > int_max_len)
		return (1);
	return (0);
}

static int	is_number(char *arg)
{
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!ft_isdigit(*arg))
		return (0);
	while (*++arg)
		if (!ft_isdigit(*arg))
			return (0);
	return (1);
}

static int	is_negative(char *arg)
{
	if (*arg++ == '-')
	{
		while (*arg == '0')
			arg++;
		if (ft_isdigit(*arg))
			return (1);
	}
	return (0);
}

int	init_rules(int *rules, int argc, char **argv)
{
	if (argc != NUMBER_OF_RULE && argc != NUMBER_OF_RULE + 1)
		return (err_ret_int(ARG_NUM_ERR_MSG
			"\nUsage: ./philo {number_of_philosophers} {time_to_die}"
			"{time_to_eat} {time_to_sleep} "
			"[number_of_times_each_philosopher_must_eat]", INPUT_ERROR));
	rules[NUMBER_OF_RULE - 1] = -1;
	while (--argc >= 1)
	{
		if (!is_number(argv[argc]) || is_negative(argv[argc]))
			return (err_ret_int(INVALID_ARG_ERR_MSG, INPUT_ERROR));
		if (is_overflow_int(argv[argc]))
			return (err_ret_int(ARG_TO_LARGE_ERR_MSG, INPUT_ERROR));
		rules[argc - 1] = ft_atoi(argv[argc]);
	}
	return (SUCCESS);
}
