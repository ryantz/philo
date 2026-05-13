#include "philo.h"

void	*print_action(void *arg)
{
	printf("%s\n", (char *)arg);
	return (NULL);
}

void
