#include "codexion.h"

void	release_dongle(t_dongle *d, unsigned int cooldown)
{
	pthread_mutex_lock(&d->dongle_lock);
	d->is_taken = 0;
	d->avaliable = get_ms() + cooldown;
	pthread_cond_broadcast(&d->dongle_cond);
	pthread_mutex_unlock(&d->dongle_lock);
}

static void	wait_cooldown(t_dongle *d)
{
	struct timespec	ts;

	ts.tv_sec = d->avaliable / 1000;
	ts.tv_nsec = (d->avaliable % 1000) * 1000000;
	pthread_cond_timedwait(&d->dongle_cond, &d->dongle_lock, &ts);
}

static unsigned int	try_take_dongle(t_coder *c, t_dongle *d)
{
	long long int	deadline;

	pthread_mutex_lock(&c->state_lock);
	deadline = c->last_compiled + c->bp_sim->config.time_to_burnout;
	pthread_mutex_unlock(&c->state_lock);
	pthread_mutex_lock(&d->dongle_lock);
	request(c, d, deadline);
	while(is_sim_running(c->bp_sim) && (d->is_taken
		|| !has_priority(&d->queue, c->id) || get_ms() < d->avaliable))
	{
		if (d->is_taken || !has_priority(&d->queue, c->id))
			pthread_cond_wait(&d->dongle_cond, &d->dongle_lock);
		else
			wait_cooldown(d);
	}
	if (!is_sim_running(c->bp_sim))
	{
		pthread_mutex_unlock(&d->dongle_lock);
		return (0);
	}
	d->is_taken = 1;
	heap_pop(&d->queue);
	pthread_mutex_unlock(&d->dongle_lock);
	log_msg(c, TAKEN_DONGLE);
	return (1);
}

unsigned int	take_dongles(t_coder *c)
{
	if (!try_take_dongle(c, c->first_dongle))
		return (0);
	if (!try_take_dongle(c, c->second_dongle))
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