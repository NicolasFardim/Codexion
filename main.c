/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:31 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/17 23:09:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	debug_print_config(t_config *c)
{
	printf("CONFIG:\n");
	printf(
		"Coders: %d\nBurnout: %d\nCompile %d\nDebug: %d\nRefactor: %d\
		\nCompiles required: %d\nCooldown dongle: %d\nScheduler: %s\n",
		c->number_of_coders, c->time_to_burnout, c->time_to_compile,
		c->time_to_debug, c->time_to_refactor, c->number_of_compiles_required,
		c->dongle_cooldown, c->scheduler);
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			flag;

	if (argc == 9)
	{
		flag = check_arg(&argv[1]);
		if (flag)
			return (1);
	}
	else
	{
		fprintf(stderr, "ERROR! must be 8 arguments!\n");
		return (1);
	}
	init_config(&argv[1], &config);
	debug_print_config(&config);
	return (0);
}
