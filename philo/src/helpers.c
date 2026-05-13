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

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

void	parse_args(t_pdata *p_data, int argc, char **argv)
{
	p_data->number_of_philosphers = argv[1];
	p_data->time_to_die = argv[2];
	p_data->time_to_eat = argv[3];
	p_data->time_to_sleep = argv[4];
	if (argc == 6)
		p_data->number_of_times_each_philosopher_must_eat = argv[5];
	else
		p_data->number_of_times_each_philosopher_must_eat = 0;
}
