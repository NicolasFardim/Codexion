/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:35 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/17 03:18:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static const char	*get_arg_name(int i)
{
	const char	*names[8];

	names[0] = "number_of_coders";
	names[1] = "time_to_burnout";
	names[2] = "time_to_compile";
	names[3] = "time_to_debug";
	names[4] = "time_to_refactor";
	names[5] = "number_of_compiles_required";
	names[6] = "dongle_cooldown";
	names[7] = "scheduler";
	return (names[i]);
}

static int	check_int(char *arg)
{
	size_t		i;
	const char	*int_max;

	if (!arg[0])
		return (0);
	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		i++;
	}
	int_max = "2147483647";
	if (strlen(arg) > 10)
		return (-2);
	if (strlen(arg) == 10)
	{
		if (strcmp(arg, int_max) > 0)
			return (-3);
	}
	return (1);
}

void	print_error(int arg_i, int error_i)
{
	printf("ERROR! argument %d (%s). ", arg_i, get_arg_name(arg_i));
	if (error_i == 0)
		printf("Empty argument!\n");
	if (error_i == -1)
		printf("Argument must be only digits!\n");
	if (error_i == -2)
		printf("Int overflow!\n");
	if (error_i == -3)
		printf("Scheduler must be either 'fifo' or 'edf'!\n");
}

int	check_arg(int argc, char **argv)
{
	unsigned int	check_args;
	int				valid;
	int				i;

	check_args = 1;
	i = 0;
	while (i < argc - 1)
	{
		valid = check_int(argv[i]);
		if (valid <= 0)
		{
			print_error(i, valid);
			check_args = 0;
		}
		i++;
	}
	printf("scheduler %s\n", argv[i]);
	return (check_args);
}
