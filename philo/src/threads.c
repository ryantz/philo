#include "philo.h"

void	*create_philo(void *arg);
void	create_pthreads(t_pdata *p_data);
void	*check_deaths(void *arg);

void	create_checking_thread(t_pdata *p_data)
{
	pthread_create(&(p_data->monitoring_thread), NULL, check_deaths, p_data);
}

void	*check_deaths(void *arg)
{
	int		i;
	long	last_meal_time;
	t_pdata	*p_data;

	p_data = (t_pdata *)arg;
	while (1)
	{
		i = 0;
		while (i < p_data->number_of_philosophers)
		{
			pthread_mutex_lock(&(p_data->lock_meal));
			last_meal_time = p_data->philo_array[i].last_meal_time;
			pthread_mutex_unlock(&(p_data->lock_meal));
			if (get_time_ms() - last_meal_time > p_data->time_to_die)
			{
				toggle_death_status(p_data);
				print_log("died", &(p_data->philo_array[i]));
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	wait_pthread(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		pthread_join(p_data->philo_array[i].thread, NULL);
		i++;
	}
}

void	create_pthreads(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		pthread_create(&(p_data->philo_array[i].thread), NULL, create_philo,
			&(p_data->philo_array[i]));
		i++;
	}
}

void	*create_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_death_status(philo->p_data))
			break ;
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
