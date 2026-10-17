#include "codexion.h"

static unsigned int	is_burned_out(t_sim *sim, unsigned int i)
{
	unsigned int	r;

	pthread_mutex_lock(&sim->coder[i].state_lock);
	if (get_ms() - sim->coder[i].last_compiled >= sim->config.time_to_burnout)
		r = 1;
	else
		r = 0;
	pthread_mutex_unlock(&sim->coder[i].state_lock);
	return (r);
}

static unsigned int	check_compiles(t_sim *sim, unsigned int i)
{
	unsigned int	r;

	pthread_mutex_lock(&sim->coder[i].state_lock);
	if (sim->coder[i].compiles >= sim->config.number_of_compiles_required)
		r = 1;
	else
		r = 0;
	pthread_mutex_unlock(&sim->coder[i].state_lock);
	return (r);
}

static unsigned int	scan_coders(t_sim *sim)
{
	unsigned int	i;
	unsigned int	complete;

	i = 0;
	complete = 0;
	while (i < sim->config.number_of_coders)
	{
		if (is_burned_out(sim, i))
		{
			set_sim_stop(sim);
			log_msg(&sim->coder[i], BURN_OUT);
			return (0);
		}
		complete += check_compiles(sim, i);
		i++;
	}
	if (complete == sim->config.number_of_coders)
	{
		set_sim_stop(sim);
		return (0);
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (is_sim_running(sim))
	{
		if (!scan_coders(sim))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}