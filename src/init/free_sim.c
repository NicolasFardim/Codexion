/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 14:50:19 by nicolas           #+#    #+#             */
/*   Updated: 2026/11/01 14:50:23 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	destroy_coders(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->coders_ready)
	{
		pthread_mutex_destroy(&sim->coder[i].state_lock);
		i++;
	}
	i = 0;
}

void	destroy_sim(t_sim *sim)
{
	destroy_coders(sim);
	if (sim->active_lock >= 4)
		pthread_cond_destroy(&sim->table_cond);
	if (sim->active_lock >= 3)
		pthread_mutex_destroy(&sim->table_lock);
	if (sim->active_lock >= 2)
		pthread_mutex_destroy(&sim->sim_lock);
	if (sim->active_lock >= 1)
		pthread_mutex_destroy(&sim->print_lock);
	free(sim->coder);
	free(sim->dongle);
	sim->coder = NULL;
	sim->dongle = NULL;
	sim->coders_ready = 0;
	sim->active_lock = 0;
}
