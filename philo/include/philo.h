/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:57:51 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 10:57:52 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum e_error
{
	WRONG_ARG_COUNT,
	WRONG_INPUT_TYPE,
};

typedef struct s_pdata	t_pdata;

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_pdata			*p_data;
}	t_philo;

typedef struct s_pdata
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				stop;
	int				max_eat;
	pthread_t		monitoring_thread;
	pthread_mutex_t	*fork_array;
	t_philo			*philo_array;
	pthread_mutex_t	lock_stop_status;
	pthread_mutex_t	lock_meal;
	pthread_mutex_t	lock_print;
}	t_pdata;

//helpers
size_t	ft_strlen(char *str);
int		is_num(char *str);
void	clean_up(t_pdata *p_data);

//mutex_helpers
void	print_log(char *str, t_philo *philo);
void	toggle_stop_status(t_pdata *p_data);
void	toggle_stop_status_and_print(t_pdata *p_data, int i);
int		get_stop_status(t_pdata *p_data);
void	get_lmt_te_status(t_pdata *p_data, long *lmt, int *te, int i);

//errors
void	print_error(int err);
int		arg_count_check(int argc);
int		arg_type_check(int argc, char **argv);

//initializer
void	init_structs(int argc, char **argv, t_pdata *p_data);

//threads
void	create_checking_thread(t_pdata *p_data);
void	create_pthreads(t_pdata *p_data);

//atoi
int		ft_atoi(const char *nptr);

//scheduler
long	get_time_ms(void);
void	single_philo_eat(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

#endif
