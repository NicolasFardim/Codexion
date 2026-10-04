#include "codexion.h"

static void	init_coders(t_sim *sim)
{
	unsigned int	i = 0;

	while(i < sim->config.number_of_coders)
	{
		sim->coder[i].id = i + 1;
		sim->coder[i].compiles = 0;
		sim->coder[i].bp_sim = sim;
		i++;
	}
}

unsigned int	init_sim(t_sim *sim)
{
	sim->coder = malloc(sizeof(t_coder) * sim->config.number_of_coders);
	if (sim->coder == NULL)
	{
		fprintf(stderr, "Error allocating memory to threads!\n");
		free(sim->coder);
		return (0);
	}
	init_coders(sim);
	return (1);
}

void	join_threads(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while(i < sim->config.number_of_coders)
	{
		if (pthread_join(sim->coder[i].thread, NULL) != 0)
			fprintf(stderr, "Couldn't join thread %d!\n", i);
		i++;
	}
	free(sim->coder);
}

unsigned int	start_threads(t_sim *sim)
{
	unsigned int	i;

	gettimeofday(&sim->start, NULL);
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if (pthread_create(
			&(sim->coder)[i].thread, NULL, routine, &(sim->coder)[i]) != 0
		)
		{
			fprintf(stderr, "Couldn't create thread %u!", i);
			join_threads(sim);
			return (0);
		}
		i++;
	}
	return (1);
}