#include "codexion.h"

void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	dongle->is_taken = 0;
	pthread_cond_broadcast(&dongle->dongle_cond);
	pthread_mutex_unlock(&dongle->dongle_lock);
}

static unsigned int	try_take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	while(is_sim_running(coder->bp_sim) && dongle->is_taken)
		pthread_cond_wait(&dongle->dongle_cond, &dongle->dongle_lock);
	if (!is_sim_running(coder->bp_sim))
	{
		pthread_mutex_unlock(&dongle->dongle_lock);
		return (0);
	}
	dongle->is_taken = 1;
	pthread_mutex_unlock(&dongle->dongle_lock);
	log_msg(coder->bp_sim, TAKEN_DONGLE);
	return (1);
}

unsigned int	take_dongles(t_coder *coder)
{
	if (!try_take_dongle(coder, coder->first_dongle))
		return (0);
	if (!try_take_dongle(coder, coder->second_dongle))
	{
		release_dongle(coder->first_dongle);
		return (0);
	}
	return (1);
}

void	wake_all_dongles(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->dongle[i].dongle_lock);
		pthread_cond_broadcast(&sim->dongle[i].dongle_cond);
		pthread_mutex_unlock(&sim->dongle[i].dongle_lock);
		i++;
	}
}