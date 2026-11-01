#include "codexion.h"

static unsigned int	is_free(t_dongle *d, long long int now)
{
	return (!d->is_taken && now >= d->avaliable);
}

static unsigned int	rival_goes_first(t_coder *c, t_dongle *d)
{
	t_coder	*rival;

	if (d->queue.size == 0 || has_priority(&d->queue, c->id))
		return (0);
	rival = &c->bp_sim->coder[d->queue.data[0].coder_id - 1];
	return (!rival->first_dongle->is_taken
		&& !rival->second_dongle->is_taken);
}

unsigned int	can_take(t_coder *c, t_dongle *a, t_dongle *b)
{
	long long int	now;

	now = get_ms();
	return (is_free(a, now) && is_free(b, now)
		&& !rival_goes_first(c, a) && !rival_goes_first(c, b));
}

void	wake_all_dongles(t_sim *sim)
{
	pthread_mutex_lock(&sim->table_lock);
	pthread_cond_broadcast(&sim->table_cond);
	pthread_mutex_unlock(&sim->table_lock);
}
