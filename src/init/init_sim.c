#include "codexion.h"

static void	init_coders(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while(i < sim->config.number_of_coders)
	{
		sim->coder[i].id = i + 1;
		sim->coder[i].compiles = 0;
		sim->coder[i].bp_sim = sim;
		i++;
	}
}

static unsigned int	init_dongles(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		sim->dongle[i].id = i + 1;
		if (pthread_mutex_init(&sim->dongle[i].dongle_lock, NULL) != 0)
		{
			destroy_dongles_lock(sim, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static unsigned int	init_sim_lock(t_sim *sim)
{
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (0);
	sim->active_lock++;
	if (pthread_mutex_init(&sim->sim_lock, NULL) != 0)
		return (0);
	sim->active_lock++;
	return (1);
}

static int	init_failed(t_sim *sim, const char *error_msg)
{
	fprintf(stderr, "Error: %s\n", error_msg);
	free(sim->coder);
	free(sim->dongle);
	sim->coder = NULL;
	sim->dongle = NULL;
	return (0);
}

unsigned int	init_sim(t_sim *sim)
{
	sim->coder = malloc(sizeof(t_coder) * sim->config.number_of_coders);
	sim->dongle = malloc(sizeof(t_dongle) * sim->config.number_of_coders);
	if (!sim->coder || !sim->dongle)
		return (init_failed(sim, "Error, malloc failed!\n"));
	if (!init_sim_lock(sim))
	{
		destroy_sim_lock(sim);
		return (init_failed(sim, "Error, simulation mutexes failed!\n"));
	}
	if (!init_dongles(sim))
	{
		destroy_sim_lock(sim);
		return (init_failed(sim, "Error, dongles failed to init!\n"));
	}
	init_coders(sim);
	return (1);
}
