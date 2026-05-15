#include "philo.h"

/*
       int gettimeofday(struct timeval *restrict tv,
                        struct timezone *_Nullable restrict tz);
*/

long	get_time_ms(void)
{
	struct timeval	time;
	long			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_in_ms);
}
