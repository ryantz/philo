/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:58:02 by ryatan            #+#    #+#             */
/*   Updated: 2026/05/16 10:58:03 by ryatan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(int err);
void	write_err(char *error_msg);

int	arg_count_check(int argc)
{
	if (argc < 5 || argc > 6)
		return (print_error(WRONG_ARG_COUNT), 1);
	return (0);
}

int	arg_type_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_num(argv[i]))
			return (print_error(WRONG_INPUT_TYPE), 1);
		i++;
	}
	return (0);
}

void	print_error(int err)
{
	if (err == WRONG_ARG_COUNT)
		write_err("Wrong argument count.");
	if (err == WRONG_INPUT_TYPE)
		write_err("Wrong input type. Inputs are not numbers.");
}

void	write_err(char *error_msg)
{
	int	len;

	len = ft_strlen(error_msg);
	write(2, error_msg, len);
	write(2, "\n", 1);
}
