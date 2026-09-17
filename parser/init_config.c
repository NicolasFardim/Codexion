/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 20:04:25 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/17 22:57:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	init_config(char **argv, t_config *config)
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
