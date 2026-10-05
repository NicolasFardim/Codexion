/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:31 by nicolas           #+#    #+#             */
/*   Updated: 2026/10/05 22:47:47 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// delete this later

static void	debug_print_config(t_config *c)
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
	// setvbuf(stdout, NULL, _IONBF, 0); printf allocate some shi for stdout
	t_sim	simulation;

	memset(&simulation, 0, sizeof(simulation));
	if (!parse_args(argc, argv, &simulation.config))
		return (1);
	debug_print_config(&simulation.config);
	printf("\n");
	if (!init_sim(&simulation))
		return (2);
	if (!start_threads(&simulation))
		return (3);
	join_threads(&simulation, simulation.config.number_of_coders);
	destroy_sim(&simulation);
	return (0);
}
