#include "philo.h"

void	parse_args(int argc, char **argv, t_pdata *p_data)
{
	p_data->number_of_philosophers = ft_atoi(argv[1]);
	p_data->time_to_die = ft_atoi(argv[2]);
	p_data->time_to_eat = ft_atoi(argv[3]);
	p_data->time_to_sleep = ft_atoi(argv[4]);
	p_data->start_time = get_time_ms();
	p_data->deaths = 0;
	p_data->fork_array = malloc(
			ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
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

void	create_pthreads(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		p_data->philo_array[i].id = i;
		pthread_create(
			&(p_data->philo_array[i].thread),
			NULL,
			create_philo,
			&(p_data->philo_array[i]));
		i++;
	}
}

void	init_forks(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		pthread_mutex_init(&(p_data->fork_array[i]), NULL);
		i++;
	}
}

void	init_philos(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		p_data->philo_array[i].id = i;
		p_data->philo_array[i].last_meal_time = 0;
		p_data->philo_array[i].times_eaten = 0;
		p_data->philo_array[i].r_fork = &(p_data->fork_array[i]);
		p_data->philo_array[i].l_fork = &(p_data->fork_array[(i + 1)
				% p_data->number_of_philosophers]);
		p_data->philo_array[i].p_data = p_data;
		i++;
	}
}
