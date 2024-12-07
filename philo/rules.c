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
	{
		ft_putendl_fd(ARG_NUM_ERR_MSG, STDERR_FILENO);
		ft_putendl_fd(USAGE_MSG, STDERR_FILENO);
		return (INPUT_ERROR);
	}
	rules[NUMBER_OF_RULE - 1] = -1;
	while (--argc >= 1)
	{
		if (!is_number(argv[argc]) || is_negative(argv[argc]))
		{
			ft_putendl_fd("Error: arguments must be a number and positive", STDERR_FILENO);
			return (INPUT_ERROR);
		}
		if (is_overflow_int(argv[argc]))
		{
			ft_putendl_fd("Error: arguments is too large (overflow)", STDERR_FILENO);
			return (INPUT_ERROR);
		}
		rules[argc - 1] = ft_atoi(argv[argc]);
	}
	return (SUCCESS);
}
