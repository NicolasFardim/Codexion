/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:50:08 by nicolas           #+#    #+#             */
/*   Updated: 2026/11/01 16:00:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	heapify_down(t_heap *heap, unsigned int parent)
{
	unsigned int	child_l;
	unsigned int	child_r;
	unsigned int	min;

	while (1)
	{
		child_l = 2 * parent + 1;
		child_r = 2 * parent + 2;
		min = parent;
		if (child_l < heap->size
			&& priority(heap->data[child_l], heap->data[min], heap->is_edf))
			min = child_l;
		if (child_r < heap->size
			&& priority(heap->data[child_r], heap->data[min], heap->is_edf))
			min = child_r;
		if (min == parent)
			return ;
		req_swap(&heap->data[parent], &heap->data[min]);
		parent = min;
	}
}

static void	heapify_up(t_heap *heap, unsigned int i)
{
	unsigned int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!priority(heap->data[i], heap->data[parent], heap->is_edf))
			return ;
		req_swap(&heap->data[i], &heap->data[parent]);
		i = parent;
	}
}

unsigned int	heap_insert(t_heap *heap, t_req req)
{
	if (heap->size == 2)
		return (0);
	heap->data[heap->size] = req;
	heapify_up(heap, heap->size);
	heap->size++;
	return (1);
}

unsigned int	heap_remove(t_heap *heap, unsigned int coder_id)
{
	unsigned int	i;

	i = 0;
	while (i < heap->size && heap->data[i].coder_id != coder_id)
		i++;
	if (i == heap->size)
		return (0);
	heap->size--;
	if (i == heap->size)
		return (1);
	heap->data[i] = heap->data[heap->size];
	heapify_down(heap, i);
	heapify_up(heap, i);
	return (1);
}
