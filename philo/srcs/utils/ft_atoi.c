/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:55:15 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/05 17:00:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	is_overflow(long long res, int sign, char c)
{
	if (res * sign > (LLONG_MAX - (c - '0')) / 10 && sign == 1)
		return (-1);
	if (res * sign < (LLONG_MIN + (c - '0')) / 10 && sign == -1)
		return (0);
	return (1);
}

static long long	cal_res(const char *s, int sign)
{
	long long	res;
	int			overflow;

	res = 0;
	while (ft_isdigit(*s))
	{
		overflow = is_overflow(res, sign, *s);
		if (overflow != 1)
			return (overflow);
		res = res * 10 + (*s - '0');
		s++;
	}
	return (sign * res);
}

int	ft_atoi(const char *s)
{
	int			sign;

	while (*s == ' ' || *s == '\t' || *s == '\n'
		|| *s == '\v' || *s == '\f' || *s == '\r')
		s++;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	return ((int)cal_res(s, sign));
}
