/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:48 by nicolas           #+#    #+#             */
/*   Updated: 2026/10/20 14:31:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include "types.h"


unsigned int	parse_args(int argc, char **argv, t_config *config);
unsigned int	validate_args(char **argv);
unsigned int	init_sim(t_sim *sim);
unsigned int	start_threads(t_sim *sim);
void			join_threads(t_sim *sim, int c);
void			destroy_sim(t_sim *sim);
void			*routine(void *arg);
void			*monitor(void *arg);
unsigned int	take_dongles(t_coder *coder);
void			release_dongle(t_dongle *dongle, unsigned int cooldown);
void			wake_all_dongles(t_sim *sim);
void			set_sim_stop(t_sim *sim);
unsigned int	is_sim_running(t_sim *sim);
long long int	get_ms(void);
void			log_msg(t_coder *coder, t_state state);

#endif
