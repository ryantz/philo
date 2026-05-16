/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:19 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 10:58:19 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_log(char *str, t_philo *philo)
{
	long	current_time;

	current_time = get_time_ms() - philo->p_data->start_time;
	pthread_mutex_lock(&(philo->p_data->lock_print));
	if (!(philo->p_data->stop))
	{
		printf("%ld %d ", current_time, philo->id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo->p_data->lock_print));
}

void	toggle_stop_status(t_pdata *p_data)
{
	pthread_mutex_lock(&(p_data->lock_stop_status));
	p_data->stop = 1;
	pthread_mutex_unlock(&(p_data->lock_stop_status));
}

void	toggle_stop_status_and_print(t_pdata *p_data, int i)
{
	long	current_time;

	pthread_mutex_lock(&(p_data->lock_print));
	pthread_mutex_lock(&(p_data->lock_stop_status));
	p_data->stop = 1;
	pthread_mutex_unlock(&(p_data->lock_stop_status));
	current_time = get_time_ms() - p_data->start_time;
	printf("%ld %d died\n", current_time, p_data->philo_array[i].id + 1);
	pthread_mutex_unlock(&(p_data->lock_print));
}

int	get_stop_status(t_pdata *p_data)
{
	int	status;

	pthread_mutex_lock(&(p_data->lock_stop_status));
	status = p_data->stop;
	pthread_mutex_unlock(&(p_data->lock_stop_status));
	return (status);
}

void	get_lmt_te_status(t_pdata *p_data, long *lmt, int *te, int i)
{
	pthread_mutex_lock(&(p_data->lock_meal));
	*lmt = p_data->philo_array[i].last_meal_time;
	*te = p_data->philo_array[i].times_eaten;
	pthread_mutex_unlock(&(p_data->lock_meal));
}
