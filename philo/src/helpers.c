#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	write_err(char *error_msg)
{
	int	len;

	len = ft_strlen(error_msg);
	write(2, error_msg, len);
	write(1, "\n", 1);
}
