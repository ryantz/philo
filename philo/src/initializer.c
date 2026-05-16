/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:11 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 14:26:12 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_args(int argc, char **argv, t_pdata *p_data);
void	init_forks(t_pdata *p_data);
void	init_philos(t_pdata *p_data);

void	init_structs(int argc, char **argv, t_pdata *p_data)
{
	parse_args(argc, argv, p_data);
	init_forks(p_data);
	pthread_mutex_init(&(p_data->lock_stop_status), NULL);
	pthread_mutex_init(&(p_data->lock_meal), NULL);
	pthread_mutex_init(&(p_data->lock_print), NULL);
	init_philos(p_data);
}

void	parse_args(int argc, char **argv, t_pdata *p_data)
{
	p_data->number_of_philosophers = ft_atoi(argv[1]);
	p_data->time_to_die = ft_atoi(argv[2]);
	p_data->time_to_eat = ft_atoi(argv[3]);
	p_data->time_to_sleep = ft_atoi(argv[4]);
	p_data->start_time = get_time_ms();
	p_data->stop = 0;
	if (argc == 6)
		p_data->max_eat = ft_atoi(argv[5]);
	else
		p_data->max_eat = -1;
	p_data->fork_array = malloc(
			ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	p_data->philo_array = malloc(
			p_data->number_of_philosophers * sizeof(t_philo));
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
		p_data->philo_array[i].times_eaten = 0;
		p_data->philo_array[i].last_meal_time = get_time_ms();
		p_data->philo_array[i].r_fork = &(p_data->fork_array[i]);
		p_data->philo_array[i].l_fork = &(p_data->fork_array[(i + 1)
				% p_data->number_of_philosophers]);
		p_data->philo_array[i].p_data = p_data;
		i++;
	}
}
