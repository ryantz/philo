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

typedef struct s_pdata t_pdata;

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
	int				deaths;
	int				number_of_times_each_philosopher_must_eat;
	t_philo			*philo_array;
	pthread_mutex_t	*fork_array;
	pthread_mutex_t	lock_print;
}	t_pdata;

// helpers
size_t	ft_strlen(char *str);
void	write_err(char *error_msg);
int		is_num(char *str);

// errors
void	print_error(int err);
int		arg_count_check(int argc);
int		arg_type_check(int argc, char **argv);

//philo assign
void	parse_args(int argc, char **argv, t_pdata *p_data);
void	create_pthreads(t_pdata *p_data);

//philo state
void	*print_action(void *arg);

//atoi
int		ft_atoi(const char *nptr);

//scheduler
long	get_time_ms(void);

#endif
