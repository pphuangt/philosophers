/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:58:50 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/07 19:58:51 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_ret_int(char *s, int return_code)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (return_code);
}

void	*err_ret_pointer(char *s, void *return_pointer)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (return_pointer);
}
