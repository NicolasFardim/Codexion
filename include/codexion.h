/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 17:56:48 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/29 15:45:04 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include "types.h"

unsigned int	parse_args(int argc, char **argv, t_config *config);
unsigned int	validate_args(char **argv);
unsigned int	init_sim(t_sim *sim);
unsigned int	start_threads(t_sim *sim);
void			join_threads(t_sim *sim);
void			*routine(void *arg);

#endif
