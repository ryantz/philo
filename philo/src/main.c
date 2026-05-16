/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:14 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 10:58:15 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
 * @params: 
 *  	number_of_philosophers
 *  	time_to_die (ms)
 *  	time_to_eat (ms)
 *  	time_to_sleep (ms)
 *  	number_of_time_each_philosopher_must_eat -> max_eat
 */
int	main(int argc, char **argv)
{
	t_pdata	p_data;

	if (arg_count_check(argc))
		return (1);
	if (arg_type_check(argc, argv))
		return (1);
	init_structs(argc, argv, &p_data);
	create_pthreads(&p_data);
	create_checking_thread(&p_data);
	pthread_join(p_data.monitoring_thread, NULL);
	clean_up(&p_data);
	return (0);
}
