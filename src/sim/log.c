#include "codexion.h"

static const char	*msg(t_state state)
{
	if (state == TAKEN_DONGLE)
		return ("has taken a dongle");
	if (state == COMPILING)
		return ("is compiling");
	if (state == DEBUGGING)
		return ("is debugging");
	if (state == REFACTORING)
		return ("is refactoring");
	if (state == BURN_OUT)
		return ("burned out");
	return ("idk");
}

void	log_msg(t_coder *coder, t_state state)
{
	pthread_mutex_lock(&coder->bp_sim->print_lock);
	if (state == BURN_OUT || is_sim_running(coder->bp_sim))
		printf("%lld %u %s\n",
			get_ms() - coder->bp_sim->start_ms, coder->id, msg(state));
	pthread_mutex_unlock(&coder->bp_sim->print_lock);
}