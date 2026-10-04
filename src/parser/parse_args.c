/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 20:04:25 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/29 15:39:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_config(char **argv, t_config *config)
{
	config->number_of_coders = atoi(argv[0]);
	config->time_to_burnout = atoi(argv[1]);
	config->time_to_compile = atoi(argv[2]);
	config->time_to_debug = atoi(argv[3]);
	config->time_to_refactor = atoi(argv[4]);
	config->number_of_compiles_required = atoi(argv[5]);
	config->dongle_cooldown = atoi(argv[6]);
	config->scheduler = argv[7];
}

unsigned int	parse_args(int argc, char **argv, t_config *cfg)
{
	if (argc != 9)
	{
		fprintf(stderr, "ERROR! Must be 8 arguments!\n");
		fprintf(stderr, "Usage: %s number_of_coders time_to_burnout "
			"time_to_compile time_to_debug time_to_refactor "
			"number_of_compiles_required dongle_cooldown fifo|edf\n",
			argv[0]);
		return (0);
	}
	if (!validate_args(&argv[1]))
		return (0);
	init_config(&argv[1], cfg);
	return (1);
}