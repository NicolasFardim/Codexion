#include "codexion.h"

void	release_dongle(t_dongle *dongle, unsigned int cooldown)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	dongle->is_taken = 0;
	dongle->avaliable = get_ms() + cooldown;
	pthread_cond_broadcast(&dongle->dongle_cond);
	pthread_mutex_unlock(&dongle->dongle_lock);
}

static void	wait_cooldown(t_dongle *d)
{
	struct timespec	ts;

	ts.tv_sec = d->avaliable / 1000;
	ts.tv_nsec = (d->avaliable % 1000) * 1000000;
	pthread_cond_timedwait(&d->dongle_cond, &d->dongle_lock, &ts);
}

static unsigned int	try_take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	while(is_sim_running(coder->bp_sim)
	&& (dongle->is_taken || get_ms() < dongle->avaliable))
	{
		if (dongle->is_taken)
			pthread_cond_wait(&dongle->dongle_cond, &dongle->dongle_lock);
		else
			wait_cooldown(dongle);
	}
	if (!is_sim_running(coder->bp_sim))
	{
		pthread_mutex_unlock(&dongle->dongle_lock);
		return (0);
	}
	dongle->is_taken = 1;
	pthread_mutex_unlock(&dongle->dongle_lock);
	log_msg(coder, TAKEN_DONGLE);
	return (1);
}

unsigned int	take_dongles(t_coder *coder)
{
	if (!try_take_dongle(coder, coder->first_dongle))
		return (0);
	if (!try_take_dongle(coder, coder->second_dongle))
		return (0);
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