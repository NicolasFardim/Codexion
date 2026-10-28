/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 22:10:56 by nicolas           #+#    #+#             */
/*   Updated: 2026/10/27 00:56:39 by nicolas          ###   ########.fr       */
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
	TAKEN_DONGLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURN_OUT
}	t_state;

typedef struct s_req
{
	unsigned int	coder_id;
	long long int	deadline;
	long long int	ticket;
}	t_req;

typedef struct s_heap
{
	t_req			data[2];
	unsigned int	size;
	unsigned int	is_edf;
}	t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	dongle_lock;
	pthread_cond_t	dongle_cond;
	t_heap			queue;
	long long int	avaliable;
	unsigned int	id;
	unsigned int	is_taken;
	unsigned int	next_ticket;
}	t_dongle;

typedef struct s_coder
{
	pthread_t		thread;
	pthread_mutex_t	state_lock;
	t_state			state;
	t_dongle		*first_dongle;
	t_dongle		*second_dongle;
	unsigned int	id;
	unsigned int	compiles;
	long long int	last_compiled;
	t_sim			*bp_sim;
}	t_coder;

struct s_sim
{
	pthread_t		monitor_thread;
	t_coder			*coder;
	t_dongle		*dongle;
	t_config		config;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
	long long int	start_ms;
	unsigned int	sim_stop;
	unsigned int	active_lock;
	unsigned int	dongles_ready;
	unsigned int	coders_ready;
};

#endif