/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:31 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/18 02:10:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	debug_print_config(t_config *c)
{
	printf("CONFIG:\n");
	printf(
		"Coders: %d\nBurnout: %d\nCompile %d\nDebug: %d\nRefactor: %d\
		\nCompiles required: %d\nCooldown dongle: %d\nScheduler: %s\n",
		c->number_of_coders, c->time_to_burnout, c->time_to_compile,
		c->time_to_debug, c->time_to_refactor, c->number_of_compiles_required,
		c->dongle_cooldown, c->scheduler);
}

void	*fake_routine(void *arg)
{
	(void)arg;
	return NULL;
}

pthread_t	*init_threads(t_config *c)
{
	pthread_t	th[c->number_of_coders];
	unsigned int	i;

	i = 0;
	while (i < c->number_of_coders)
	{
		if (pthread_create(&th[i], NULL, fake_routine, NULL) != 0)
			fprintf(stderr, "Couldn't create thread %u!", i);
		i++;
	}
	return (th);
}

void	join_threads(pthread_t	*th)
{
	while(*th)
	{
		if (pthread_join(&*th, NULL) != 0)
			fprintf(stderr, "Couldn't joing thread!");
		th++;
	}
}

int	main(int argc, char **argv)
{
	t_config	config;
	int			flag;

	if (argc == 9)
	{
		flag = check_arg(&argv[1]);
		if (flag)
			return (1);
	}
	else
	{
		fprintf(stderr, "ERROR! must be 8 arguments!\n");
		return (1);
	}
	init_config(&argv[1], &config);
	debug_print_config(&config);
	init_threads(&config);
	return (0);
}
