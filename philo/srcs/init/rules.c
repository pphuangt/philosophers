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

static int	is_overflow(char *s)
{
	int		i;
	int		len;
	int		int_max_len;
	char	*int_max;

	i = 0;
	int_max = "2147483647";
	int_max_len = ft_strlen(int_max);
	while (s[i] == '0')
		i++;
	len = 0;
	while (ft_isdigit(s[i + len]))
		len++;
	if ((len == int_max_len && ft_strncmp(&s[i], int_max, len) > 0)
		|| len > int_max_len)
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
		return (err_ret(ARG_NUM_ERR_MSG
				"\nUsage: ./philo {number_of_philosophers} {time_to_die}"
				"{time_to_eat} {time_to_sleep} "
				"[number_of_times_each_philosopher_must_eat]", INPUT_ERROR));
	rules[NUMBER_OF_RULE - 1] = -1;
	while (--argc >= 1)
	{
		if (!is_number(argv[argc]) || is_negative(argv[argc]))
			return (err_ret(INVALID_ARG_ERR_MSG, INPUT_ERROR));
		if (is_overflow(argv[argc]))
			return (err_ret(ARG_TO_LARGE_ERR_MSG, INPUT_ERROR));
		rules[argc - 1] = ft_atoi(argv[argc]);
	}
	return (SUCCESS);
}
