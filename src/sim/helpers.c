#include "codexion.h"

long long int	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	log_output(t_coder *coder)
{
	pthread_mutex_lock(&coder->bp_sim->print_lock);
	printf("%lld %u\n", get_ms() - coder->bp_sim->start_ms, coder->id);
	pthread_mutex_unlock(&coder->bp_sim->print_lock);
}
