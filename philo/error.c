#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static void	ft_putendl_fd(char *s, int fd)
{
	size_t	s_len;

	if (!s)
		return ;
	s_len = ft_strlen(s);
	write(fd, s, s_len);
	write(fd, "\n", 1);
}

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
