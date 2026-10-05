/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:48 by nicolas           #+#    #+#             */
/*   Updated: 2026/10/06 00:44:31 by nicolas          ###   ########.fr       */
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
void			join_threads(t_sim *sim, unsigned int c);
void			destroy_dongles_lock(t_sim *sim, unsigned int count);
void			destroy_sim_lock(t_sim *sim);
void			destroy_sim(t_sim *sim);
void			*routine(void *arg);
long long int	get_ms(void);
void			log_output(t_coder *coder);

#endif
