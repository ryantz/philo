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
};

// helpers
size_t	ft_strlen(char *str);
void	write_err(char *error_msg);


// errors
void	print_error(int err);

#endif
