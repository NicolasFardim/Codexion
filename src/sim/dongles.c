/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:10:12 by nicolas           #+#    #+#             */
/*   Updated: 2026/11/01 15:16:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	release_dongle(t_dongle *d, unsigned int cooldown)
{
	d->is_taken = 0;
	d->avaliable = get_ms() + cooldown;
}

static void	request_both(t_coder *c, t_dongle *a, t_dongle *b)
{
	long long int	deadline;

	pthread_mutex_lock(&c->state_lock);
	deadline = c->last_compiled + c->bp_sim->config.time_to_burnout;
	pthread_mutex_unlock(&c->state_lock);
	request(c, a, deadline);
	if (b != a)
		request(c, b, deadline);
}

static void	wait_turn(t_sim *sim, t_dongle *a, t_dongle *b)
{
	struct timespec	ts;
	long long int	until;

	until = a->avaliable;
	if (b->avaliable > until)
		until = b->avaliable;
	if (until <= get_ms())
		until = get_ms() + 1;
	ts.tv_sec = until / 1000;
	ts.tv_nsec = (until % 1000) * 1000000;
	pthread_cond_timedwait(&sim->table_cond, &sim->table_lock, &ts);
}

static int	try_take_dongles(t_coder *c, t_dongle *a, t_dongle *b)
{
	while (1)
	{
		if (!is_sim_running(c->bp_sim))
		{
			pthread_mutex_unlock(&c->bp_sim->table_lock);
			return (0);
		}
		if (a != b && can_take(c, a, b))
			return (1);
		wait_turn(c->bp_sim, a, b);
	}
}

unsigned int	take_dongles(t_coder *c)
{
	t_dongle	*a;
	t_dongle	*b;

	a = c->first_dongle;
	b = c->second_dongle;
	pthread_mutex_lock(&c->bp_sim->table_lock);
	request_both(c, a, b);
	if (!try_take_dongles(c, a, b))
		return (0);
	heap_remove(&a->queue, c->id);
	heap_remove(&b->queue, c->id);
	a->is_taken = 1;
	b->is_taken = 1;
	pthread_mutex_unlock(&c->bp_sim->table_lock);
	log_msg(c, TAKEN_DONGLE);
	log_msg(c, TAKEN_DONGLE);
	return (1);
}
