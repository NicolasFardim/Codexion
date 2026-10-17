#include "codexion.h"

long long int	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	set_sim_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->sim_lock);
	sim->sim_stop = 1;
	pthread_mutex_unlock(&sim->sim_lock);
	wake_all_dongles(sim);
}

unsigned int	is_sim_running(t_sim *sim)
{
	unsigned int	r;

	pthread_mutex_lock(&sim->sim_lock);
	if (sim->sim_stop == 1)
		r = 0;
	else
		r = 1;
	pthread_mutex_unlock(&sim->sim_lock);
	return (r);
}
