/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:31 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/20 14:45:55 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// delete this later
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

// delete this later
void	*fake_routine(void *arg)
{
	(void)arg;
	return NULL;
}

static unsigned int	join_threads(pthread_t *th, unsigned int n_coders)
{
	unsigned int	i;
	unsigned int	check;

	check = 1;
	i = 0;
	while(i < n_coders)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			fprintf(stderr, "Couldn't join thread %d!\n", i);
			check = 0;
		}
		i++;
	}
	free(th);
	return (check);
}

static unsigned int	init_threads(pthread_t **th, unsigned int n_coders)
{
	unsigned int	i;

	i = 0;
	*th = malloc(sizeof(pthread_t) * n_coders);
	if (*th == NULL)
	{
		fprintf(stderr, "Error allocating memory to threads!\n");
		return (0);
	}
	while (i < n_coders)
	{
		/* test to force fail (it works will free every initialized thread
		also works if the first '0' fails)
			if (i == 3) {
			fprintf(stderr, "Simulate problem");
			join_threads(*th, i);
			return (0);
		} */
		if (pthread_create(&(*th)[i], NULL, fake_routine, NULL) != 0)
		{
			fprintf(stderr, "Couldn't create thread %u!", i);
			join_threads(*th, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	// setvbuf(stdout, NULL, _IONBF, 0); printf allocate some shi for stdout
	pthread_t	*th;
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
	return(1);
	if (!init_threads(&th, config.number_of_coders))
		return (1);
	join_threads(th, config.number_of_coders);

	return (0);
}
