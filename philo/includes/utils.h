/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:28:09 by pphuangt          #+#    #+#             */
/*   Updated: 2024/12/09 10:28:11 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

int		ft_isdigit(int c);
int		ft_atoi(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_timeradd(struct timeval *a, struct timeval *b, struct timeval *res);
void	ft_timersub(struct timeval *a, struct timeval *b, struct timeval *res);
int		err_ret(char *s, int return_code);

#endif
