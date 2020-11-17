/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/17 19:55:16 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_error(void)
{
	write(2, "malloc: *** error: pointer being freed was not allocated\n", 58);
	exit(1);
}

t_heap_and_block *find_block(t_heap *heap, void *ptr)
{
	t_block *tmp;

	while (heap)
	{
		tmp = HEAP_SHIFT(heap);
		while (tmp)
		{
			if (BLOCK_SHIFT(tmp) == ptr)
				return (&((t_heap_and_block){heap, tmp}));
			tmp = tmp->next;
		}
		heap = heap->next;
	}
	return (NULL);
}

void	set_block_free(t_heap_and_block *data)
{
	data->block->freed = 1;
	data->heap->block_amount--;
}

void	merge_blocks(t_heap_and_block *data)
{
	if (data->block->prev && data->block->prev->freed)
	{
		data->block->prev->data_size += data->block->data_size + sizeof(t_block);
		data->block->prev->next = data->block->next;
		if (data->block->next)
			data->block->next->prev = data->block->prev;
		data->block = data->block->prev;
	}
	if (data->block->next && data->block->next->freed)
	{
		data->block->data_size += data->block->next->data_size;
		if (data->block->next->next)
			data->block->next->next->prev = data->block;
		data->block->next = data->block->next->next;
	}
}

void	free(void *ptr)
{
	t_heap_and_block *data;

	if (!ptr)
		return ;
	// iterate through heaps, checking if block pointer
	// matches ptr
	if (!(data = find_block(g_malloc.tiny, ptr)))
		if (!(data = find_block(g_malloc.small, ptr)))
			if (!(data = find_block(g_malloc.large, ptr)))
				free_error();
	// set block to "not in use"
	set_block_free(data);
	//merge with nearby blocks if possible
	merge_blocks(data);
	// free heap with munmap if no blocks left
	if (data->heap->block_amount == 0)
		munmap(data->heap, data->heap->size);
	// memory leak if not all empty heaps freed?
}
