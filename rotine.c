#include "codexion.h"

void	*routine(void *arg)
{
	t_coder *coder = (t_coder *)arg;

	printf("%d\n", coder->id);
	return (NULL);
}

void	start_coders(t_coder *coder, t_config *config, int i)
{
	coder->id = i + 1;
	coder->config;
}