/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:35 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/17 22:58:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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

static int	print_error(int arg_i, int error_i)
{
	fprintf(stderr, "ERROR! Argument: %d (%s). ", arg_i, get_arg_name(arg_i));
	if (error_i == 0)
		fprintf(stderr, "Empty argument!\n");
	if (error_i == -1)
		fprintf(stderr, "Argument must be only digits!\n");
	if (error_i == -2)
		fprintf(stderr, "Int overflow!\n");
	if (error_i == -3)
		fprintf(stderr, "Must be either 'fifo' or 'edf'!\n");
	if (error_i == -4)
		fprintf(stderr, "Must have at least 1 coder!\n");
	return (1);
}

/* ! Right now I allow value 0 for parameters (1 to 6)... Maybe I have to change
this later */
static int	check_arg_int(char *arg)
{
	size_t		i;
	const char	*int_max;

	if (!arg[0])
		return (0);
	while (*arg == '0')
		arg++;
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
			return (-2);
	}
	return (1);
}

static int	is_arg_zero(char *arg)
{
	while (*arg == '0')
		arg++;
	if (!*arg)
		return (1);
	return (0);
}

/* ! once flag is set to 1, it should not comeback to 0 */
int	check_arg(char **argv)
{
	unsigned int	flag;
	int				valid;
	int				i;

	flag = 0;
	i = 0;
	if (argv[0][0] && is_arg_zero(argv[0]))
		flag = print_error(0, -4);
	while (i < 7)
	{
		valid = check_arg_int(argv[i]);
		if (valid <= 0)
			flag = print_error(i, valid);
		i++;
	}
	if (strcmp(argv[7], "fifo") != 0 && strcmp(argv[7], "edf") != 0)
		flag = print_error(7, -3);
	return (flag);
}
