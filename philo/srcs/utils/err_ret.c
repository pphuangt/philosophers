/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ret.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:28:53 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 10:28:54 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	err_ret(char *s, int return_code)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (return_code);
}
