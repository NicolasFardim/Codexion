/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 22:10:56 by nicolas           #+#    #+#             */
/*   Updated: 2026/10/06 00:44:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <sys/time.h>

typedef	struct s_sim	t_sim;

typedef struct s_config
{
	unsigned int	number_of_coders;
	unsigned int	time_to_burnout;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refactor;
	unsigned int	number_of_compiles_required;
	unsigned int	dongle_cooldown;
	char			*scheduler;
}	t_config;

typedef enum e_state
{
	COMPILING,
	DEBUGGING,
	REFACTORING
}	t_state;

typedef struct s_dongle
{
	pthread_mutex_t	dongle_lock;
	unsigned int	id;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	t_state			state;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	unsigned int	id;
	unsigned int	compiles;
	t_sim			*bp_sim;
}	t_coder;

struct s_sim
{
	t_coder			*coder;
	t_dongle		*dongle;
	t_config		config;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
	long long int	start_ms;
	unsigned int	active_lock;
};

#endif