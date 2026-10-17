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

static void	destroy_dongles(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->dongles_ready)
	{
		pthread_mutex_destroy(&sim->dongle[i].dongle_lock);
		pthread_cond_destroy(&sim->dongle[i].dongle_cond);
		i++;
	}
}

void	destroy_sim(t_sim *sim)
{
	destroy_coders(sim);
	destroy_dongles(sim);
	if (sim->active_lock >= 2)
		pthread_mutex_destroy(&sim->sim_lock);
	if (sim->active_lock >= 1)
		pthread_mutex_destroy(&sim->print_lock);
	free(sim->coder);
	free(sim->dongle);
	sim->coder = NULL;
	sim->dongle = NULL;
	sim->coders_ready = 0;
	sim->dongles_ready = 0;
	sim->active_lock = 0;
}