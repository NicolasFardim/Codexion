#include "codexion.h"

void	destroy_dongles_lock(t_sim *sim, unsigned int count)
{
	unsigned int	i;

	i = 0;
	while(i < count)
	{
		pthread_mutex_destroy(&sim->dongle[i].dongle_lock);
		i++;
	}
}

void	destroy_sim_lock(t_sim *sim)
{
	if (sim->active_lock >= 2)
		pthread_mutex_destroy(&sim->sim_lock);
	if (sim->active_lock >= 1)
		pthread_mutex_destroy(&sim->print_lock);
}

void	join_threads(t_sim *sim, unsigned int c)
{
	unsigned int	i;

	i = 0;
	while(i < c)
	{
		if (pthread_join(sim->coder[i].thread, NULL) != 0)
			fprintf(stderr, "Couldn't join thread %d!\n", i);
		i++;
	}
}

void	destroy_sim(t_sim *sim)
{
	destroy_dongles_lock(sim, sim->config.number_of_coders);
	destroy_sim_lock(sim);
	free(sim->coder);
	free(sim->dongle);
	sim->coder = NULL;
	sim->dongle = NULL;
}