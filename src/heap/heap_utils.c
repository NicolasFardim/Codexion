/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:49:40 by nicolas           #+#    #+#             */
/*   Updated: 2026/11/01 15:49:41 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	req_swap(t_req *a, t_req *b)
{
	t_req	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

unsigned int	has_priority(t_heap *heap, unsigned int coder_id)
{
	if (heap->size == 0)
		return (0);
	return (heap->data[0].coder_id == coder_id);
}

unsigned int	priority(t_req a, t_req b, unsigned int is_edf)
{
	if (is_edf && a.deadline != b.deadline)
		return (a.deadline < b.deadline);
	return (a.ticket < b.ticket);
}

void	heap_init(t_heap *heap, t_sim *sim)
{
	heap->size = 0;
	heap->is_edf = (strcmp("edf", sim->config.scheduler) == 0);
}
