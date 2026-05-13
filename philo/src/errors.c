#include "philo.h"

void	print_error(int err)
{
	if (err == WRONG_ARG_COUNT)
		write_err("Wrong argument count.");
}
