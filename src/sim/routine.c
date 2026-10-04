#include "codexion.h"

long long int	elapsed_ms(struct timeval *start)
{
	struct timeval	sim_now;
	long long int 	ms;

	gettimeofday(&sim_now, NULL);
	ms = (sim_now.tv_sec - start->tv_sec) * 1000
	+ (sim_now.tv_usec - start->tv_usec) / 1000;
	return (ms);
}

void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compiles < coder->bp_sim->config.number_of_compiles_required)
	{
		printf("%lld %d\n", elapsed_ms(&coder->bp_sim->start), coder->id);
		coder->compiles += 1;
	}
	return (NULL);
}
