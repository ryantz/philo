/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:22 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 10:58:23 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	time;
	long			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}

void	single_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_log("has taken a fork", philo);
	usleep(philo->p_data->time_to_die * 1000);
	pthread_mutex_unlock(philo->l_fork);
	return ;
}

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_log("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print_log("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_log("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_log("has taken a fork", philo);
	}
	pthread_mutex_lock(&(philo->p_data->lock_meal));
	philo->last_meal_time = get_time_ms();
	philo->times_eaten++;
	pthread_mutex_unlock(&(philo->p_data->lock_meal));
	print_log("is eating", philo);
	usleep(philo->p_data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_log("is sleeping", philo);
	usleep(philo->p_data->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_log("is thinking", philo);
}
