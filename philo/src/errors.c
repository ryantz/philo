#include "philo.h"

void	print_error(int err);

int	arg_count_check(int argc)
{
	if (argc < 5 || argc > 6)
		return (print_error(WRONG_ARG_COUNT), 1);
	return (0);
}

int	arg_type_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if(!is_num(argv[i]))
			return (print_error(WRONG_INPUT_TYPE), 1);
		i++;
	}
	return (0);
}

void	print_error(int err)
{
	if (err == WRONG_ARG_COUNT)
		write_err("Wrong argument count.");
	if (err == WRONG_INPUT_TYPE)
		write_err("Wrong input type. Inputs are not numbers.");
}

