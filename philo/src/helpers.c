/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:08 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 14:33:48 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_sleep(long sleep_duration, t_pdata *p_data)
{
	long	end_time;

	end_time = get_time_ms() + sleep_duration;
	while (get_time_ms() < end_time)
	{
		if (get_stop_status(p_data))
			break ;
		usleep(100);
	}
}

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

void	clean_up(t_pdata *p_data)
{
	int	i;

	i = 0;
	while (i < p_data->number_of_philosophers)
	{
		pthread_mutex_destroy(&(p_data->fork_array[i]));
		i++;
	}
	pthread_mutex_destroy(&(p_data->lock_stop_status));
	pthread_mutex_destroy(&(p_data->lock_meal));
	pthread_mutex_destroy(&(p_data->lock_print));
	free(p_data->fork_array);
	free(p_data->philo_array);
}
