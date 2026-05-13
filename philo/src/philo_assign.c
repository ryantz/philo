#include "philo.h"

void	parse_args(t_pdata *p_data, int argc, char **argv)
{
	p_data->number_of_philosophers = argv[1];
	p_data->time_to_die = argv[2];
	p_data->time_to_eat = argv[3];
	p_data->time_to_sleep = argv[4];
	if (argc == 6)
		p_data->number_of_times_each_philosopher_must_eat = argv[5];
	else
		p_data->number_of_times_each_philosopher_must_eat = 0;
}

void	*print_action(void *arg)
{
	printf("%s\n", (char *)arg);
	return (NULL);
}

void	create_pthreads(t_pdata *p_data)
{
	int				i;
	pthread_t		*thread_array;

	i = 0;
	thread_array = malloc(p_data->number_of_philosophers * sizeof(pthread_t));
	while (i < p_data->number_of_philosophers)
	{
		pthread_create(&(thread_array[i]), NULL, print_action, NULL);
		i++;
	}
}
