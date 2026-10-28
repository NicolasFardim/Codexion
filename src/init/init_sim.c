#include "codexion.h"

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

static unsigned int	init_dongles(t_sim *sim)
{
	t_dongle	*d;

	while (sim->dongles_ready < sim->config.number_of_coders)
	{
		d = &sim->dongle[sim->dongles_ready];
		d->id = sim->dongles_ready + 1;
		d->is_taken = 0;
		d->avaliable = 0;
		d->next_ticket = 0;
		heap_init(&d->queue, sim);
		if (pthread_mutex_init(&d->dongle_lock, NULL) != 0)
			return (0);
		if (pthread_cond_init(&d->dongle_cond, NULL) != 0)
		{
			pthread_mutex_destroy(&d->dongle_lock);
			return (0);
		}
		sim->dongles_ready++;
	}
	return (1);
}

static unsigned int	init_coders(t_sim *sim)
{
	unsigned int	n;
	t_coder			*c;

	n = sim->config.number_of_coders;
	while (sim->coders_ready < n)
	{
		c = &sim->coder[sim->coders_ready];
		c->id = sim->coders_ready + 1;
		c->compiles = 0;
		c->last_compiled = 0;
		c->bp_sim = sim;
		c->first_dongle = &sim->dongle[sim->coders_ready];
		c->second_dongle = &sim->dongle[(sim->coders_ready + 1) % n];
		if (c->second_dongle->id < c->first_dongle->id)
		{
			c->first_dongle = &sim->dongle[(sim->coders_ready + 1) % n];
			c->second_dongle = &sim->dongle[sim->coders_ready];
		}
		if (pthread_mutex_init(&c->state_lock, NULL) != 0)
			return (0);
		sim->coders_ready++;
	}
	return (1);
}

unsigned int	init_sim(t_sim *sim)
{
	const char	*err;

	err = NULL;
	sim->coder = malloc(sizeof(t_coder) * sim->config.number_of_coders);
	sim->dongle = malloc(sizeof(t_dongle) * sim->config.number_of_coders);
	if (!sim->coder || !sim->dongle)
		err = "malloc failed";
	else if (!init_sim_lock(sim))
		err = "simulation mutex init failed";
	else if (!init_dongles(sim))
		err = "dongle init failed";
	else if (!init_coders(sim))
		err = "coder init failed";
	if (!err)
		return (1);
	fprintf(stderr, "Error: %s\n", err);
	destroy_sim(sim);
	return (0);
}