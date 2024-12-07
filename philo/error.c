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
