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

typedef struct s_pdata
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	t_philo			*philo_array;
	pthread_t		*thread_array;
	pthread_mutex_t	*fork_array;
}	t_pdata;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

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

#endif
