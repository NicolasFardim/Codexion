#include "codexion.h"


static void	compiling(t_coder *coder)
{
	pthread_mutex_lock(&coder->state_lock);
	coder->last_compiled = get_ms();
	pthread_mutex_unlock(&coder->state_lock);
	log_msg(coder, COMPILING);
	usleep(coder->bp_sim->config.time_to_compile * 1000);
	pthread_mutex_lock(&coder->state_lock);
	coder->compiles++;
	pthread_mutex_unlock(&coder->state_lock);
}

static void	debug_and_refactor(t_coder *coder)
{
	log_msg(coder, DEBUGGING);
	usleep(coder->bp_sim->config.time_to_debug * 1000);
	log_msg(coder, REFACTORING);
	usleep(coder->bp_sim->config.time_to_refactor * 1000);
}

void	*routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->bp_sim;
	while (is_sim_running(sim))
	{
		if (!take_dongles(coder))
			return (NULL);
		compiling(coder);
		release_dongle(coder->first_dongle, sim->config.dongle_cooldown);
		release_dongle(coder->second_dongle, sim->config.dongle_cooldown);
		debug_and_refactor(coder);
	}
	return (NULL);
}
