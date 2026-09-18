/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 22:10:56 by nicolas           #+#    #+#             */
/*   Updated: 2026/09/18 01:49:33 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef struct s_config
{
	unsigned int	number_of_coders;
	unsigned int	time_to_burnout;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refactor;
	unsigned int	number_of_compiles_required;
	unsigned int	dongle_cooldown;
	char	*scheduler;
}	t_config;

#endif