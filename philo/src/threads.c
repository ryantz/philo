#include "philo.h"

void	parse_args(int argc, char **argv, t_pdata *p_data)
{
	p_data->number_of_philosophers = ft_atoi(argv[1]);
	p_data->time_to_die = ft_atoi(argv[2]);
	p_data->time_to_eat = ft_atoi(argv[3]);
	p_data->time_to_sleep = ft_atoi(argv[4]);
	p_data->fork_array = malloc(
			ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	p_data->thread_array = malloc(
			p_data->number_of_philosophers * sizeof(pthread_t));
	p_data->philo_array = malloc(
			p_data->number_of_philosophers * sizeof(t_philo));
	if (argc == 6)
		p_data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		p_data->number_of_times_each_philosopher_must_eat = 0;
}

void	*create_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philo thread created with philo id %d\n", philo->id);
	return (NULL);
}

void	create_threads(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		philo_array[i].id = i;
		pthread_create(
			&(p_data->thread_array[i]),
			NULL,
			create_philo,
			&(p_data->philo_array[i]));
		i++;
	}
}

void	init_mutex(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		pthread_mutex_init(&(p_data->fork_array[i]), NULL);
		i++;
	}
}
