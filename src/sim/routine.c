/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:03:22 by nicolas           #+#    #+#             */
/*   Updated: 2026/11/03 09:18:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	compiling(t_coder *coder)
{
	pthread_mutex_lock(&coder->state_lock);
	coder->last_compiled = get_ms();
	pthread_mutex_unlock(&coder->state_lock);
	log_msg(coder, COMPILING);
	ms_sleep(coder->bp_sim, coder->bp_sim->config.time_to_compile);
	pthread_mutex_lock(&coder->state_lock);
	coder->compiles++;
	pthread_mutex_unlock(&coder->state_lock);
}

static void	debug_and_refactor(t_coder *coder)
{
	log_msg(coder, DEBUGGING);
	ms_sleep(coder->bp_sim, coder->bp_sim->config.time_to_debug);
	log_msg(coder, REFACTORING);
	ms_sleep(coder->bp_sim, coder->bp_sim->config.time_to_debug);
}

static void	release_dongles(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->bp_sim;
	pthread_mutex_lock(&sim->table_lock);
	release_dongle(coder->first_dongle, sim->config.dongle_cooldown);
	release_dongle(coder->second_dongle, sim->config.dongle_cooldown);
	pthread_cond_broadcast(&sim->table_cond);
	pthread_mutex_unlock(&sim->table_lock);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->bp_sim;
	while (is_sim_running(sim))
	{
		if (!take_dongles(coder))
			return (NULL);
		compiling(coder);
		release_dongles(coder);
		debug_and_refactor(coder);
	}
	return (NULL);
}
