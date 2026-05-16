/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:28 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 14:23:11 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*create_philo(void *arg);
void	create_pthreads(t_pdata *p_data);
void	*check_stopping_criteria(void *arg);

void	create_checking_thread(t_pdata *p_data)
{
	pthread_create(&(p_data->monitoring_thread), NULL,
		check_stopping_criteria, p_data);
}

void	*check_stopping_criteria(void *arg)
{
	int		i;
	long	last_meal_time;
	int		times_eaten;
	int		philo_thread_limit;
	t_pdata	*p_data;

	p_data = (t_pdata *)arg;
	while (1)
	{
		i = 0;
		philo_thread_limit = 0;
		while (i < p_data->number_of_philosophers)
		{
			get_lmt_te_status(p_data, &last_meal_time, &times_eaten, i);
			if ((get_time_ms() - last_meal_time > p_data->time_to_die))
				return (toggle_stop_status_and_print(p_data, i), NULL);
			if ((p_data->max_eat != -1) && (times_eaten >= p_data->max_eat))
				philo_thread_limit++;
			i++;
		}
		if (philo_thread_limit == p_data->number_of_philosophers)
			return (toggle_stop_status(p_data), NULL);
		usleep(1000);
	}
	return (NULL);
}

void	join_philo_pthreads(t_pdata *p_data)
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
	if (philo->p_data->number_of_philosophers == 1)
		return (single_philo_eat(philo), NULL);
	pthread_mutex_lock(&(philo->p_data->lock_meal));
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&(philo->p_data->lock_meal));
	if (philo->p_data->number_of_philosophers > 2 && philo->id % 2 == 0)
		usleep(1000);
	while (!get_stop_status(philo->p_data))
	{
		philo_eat(philo);
		if (get_stop_status(philo->p_data))
			break ;
		philo_sleep(philo);
		if (get_stop_status(philo->p_data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
