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
	pthread_mutex_t	*fork_array;
}	t_pdata;

typedef struct s_philo
{
	int	id;
}	t_philo

// helpers
size_t	ft_strlen(char *str);
void	write_err(char *error_msg);
int		is_num(char *str);
void	parse_args(t_pdata *p_data, int argc, char **argv);

// errors
void	print_error(int err);
int		arg_count_check(int argc);
int		arg_type_check(int argc, char **argv);

//philo assign
void	parse_args(t_pdata *p_data, int argc, char **argv);

//philo state
void	*print_action(void *arg);

#endif
