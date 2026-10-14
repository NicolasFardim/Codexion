#include "codexion.h"

static unsigned int	thread_failed(t_sim *sim, int i)
{
	fprintf(stderr, "Couldn't create thread %u!\n", i);
	set_sim_stop(sim);
	join_threads(sim, i);
	destroy_sim(sim);
	return (0);
}

unsigned int	start_threads(t_sim *sim)
{
	unsigned int	i;

	sim->start_ms = get_ms();
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		sim->coder[i].last_compiled = sim->start_ms;
		i++;
	}
	if (pthread_create(&(sim->monitor_thread), NULL, monitor, sim) != 0)
		return (thread_failed(sim, -1));
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		if (
			pthread_create(
				&(sim->coder)[i].thread, NULL, routine, &(sim->coder)[i]) != 0
			)
			return (thread_failed(sim, i));
		i++;
	}
	return (1);
}


// Using return value of join just for debug, remove later
void	join_threads(t_sim *sim, int c)
{
	int	i;

	i = 0;
	if (c == -1)
	{
		fprintf(stderr, "Monitor failed, any thread was created!\n");
		return ;
	}
	if (pthread_join(sim->monitor_thread, NULL) != 0)
		fprintf(stderr, "Couldn't join monitor thread!\n");
	while (i < c)
	{
		if (pthread_join(sim->coder[i].thread, NULL) != 0)
			fprintf(stderr, "Couldn't join thread %d!\n", i);
		i++;
	}
}
