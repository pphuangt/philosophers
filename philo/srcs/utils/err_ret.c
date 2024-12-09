#include "utils.c"

int	err_ret(char *s, int return_code)
{
	ft_putendl_fd(s, STDERR_FILENO);
	return (return_code);
}
