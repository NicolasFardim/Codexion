#include "codexion.h"

unsigned int	start_threads(t_sim *sim)
{
	unsigned int	i;

	sim->start_ms = get_ms();
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if (pthread_create(
			&(sim->coder)[i].thread, NULL, routine, &(sim->coder)[i]) != 0
		)
		{
			fprintf(stderr, "Couldn't create thread %u!\n", i);
			join_threads(sim, i);
			destroy_sim(sim);
			return (0);
		}
		i++;
	}
	return (1);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compiles < coder->bp_sim->config.number_of_compiles_required)
	{
		log_output(coder);
		coder->compiles += 1;
	}
	return (NULL);
}
