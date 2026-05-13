#include "philo.h"

void	*test(void *arg)
{
	printf("test thread..\n");
	printf("%p\n", arg);
	return NULL;
}

int	main(void)
{
	pthread_t	pthread_id;

	pthread_create(&pthread_id, NULL, test, NULL);
	pthread_join(pthread_id, NULL);
	printf("main thread ends.\n");
	return (0);
}

//int	main(int argc, char **argv)
//{
//	char	*number_of_philosophers;
//	char	*time_to_die;
//	char	*time_to_eat;
//	char	*time_to_sleep;
//	char	*number_of_times_each_philosopher_must_eat;
//
//	if (argc < 5 || argc > 6)
//		return (print_error(WRONG_ARG_COUNT), 1);
//	number_of_philosophers = argv[1];
//	time_to_die = argv[2];
//	time_to_eat = argv[3];
//	time_to_sleep = argv[4];
//	if (argc == 6)
//		number_of_times_each_philosopher_must_eat = argv[5];
//	printf("%s\n", number_of_philosophers);
//	printf("%s\n", time_to_die);
//	printf("%s\n", time_to_eat);
//	printf("%s\n", time_to_sleep);
//	printf("%s\n", number_of_times_each_philosopher_must_eat);
//	return (0);
//}
