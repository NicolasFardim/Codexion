/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:31 by nicolas           #+#    #+#             */
/*   Updated: 2026/10/30 15:53:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_sim	simulation;

	memset(&simulation, 0, sizeof(simulation));
	if (!parse_args(argc, argv, &simulation.config))
		return (1);
	if (!init_sim(&simulation))
		return (2);
	if (!start_threads(&simulation))
		return (3);
	join_threads(&simulation, simulation.config.number_of_coders);
	destroy_sim(&simulation);
	return (0);
}
