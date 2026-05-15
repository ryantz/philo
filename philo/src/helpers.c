#include "philo.h"

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

void	write_err(char *error_msg)
{
	int	len;

	len = ft_strlen(error_msg);
	write(2, error_msg, len);
	write(1, "\n", 1);
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

void	print_log(char *str, t_philo *philo)
{
	long	current_time;

	current_time = get_time_ms() - philo->p_data->start_time;
	pthread_mutex_lock(&(philo->p_data->lock_print));
	printf("%ld %d ", current_time, philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&(philo->p_data->lock_print));
}

int	get_death_status(t_pdata *p_data)
{
	int	status;

	pthread_mutex_lock(&(p_data->lock_death));
	status = p_data->deaths;
	pthread_mutex_unlock(&(p_data->lock_death));
	return (status);
}
