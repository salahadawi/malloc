/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/24 15:20:50 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_error(void)
{
	if (g_malloc.debug_free)
	{
		write(2, "malloc: *** error: pointer being freed was not allocated\n",
		58);
		exit(1);
	}
}

int	find_block(t_heap *heap, void *ptr)
{
	t_block *tmp;
	size_t	i;

	while (heap)
	{
		i = 0;
		tmp = HEAP_SHIFT(heap);
		while (i < heap->block_amount)
		{
			if (BLOCK_SHIFT(tmp) == ptr)
			{
				g_malloc.heap = heap;
				g_malloc.block = tmp;
				return (1);
			}
			tmp = tmp->next;
			i++;
		}
		heap = heap->next;
	}
	return (0);
}

void	set_block_free(t_heap *heap, t_block *block)
{
	block->freed = 1;
	heap->blocks_freed++;
}

void	merge_blocks(t_block *block)
{
	if (block->prev && block->prev->freed)
	{
		block->prev->data_size += block->data_size + sizeof(t_block);
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		block = block->prev;
	}
	if (block->next && block->next->freed)
	{
		block->data_size += block->next->data_size;
		if (block->next->next)
			block->next->next->prev = block;
		block->next = block->next->next;
	}
}

void	remove_heap(t_heap *heap)
{
	t_heap *next;

	if (heap->next)
		heap->next->prev = heap->prev;
	if (heap->prev)
		heap->prev->next = heap->next;
	next = heap->next;
	munmap(heap, heap->size);
	if (heap == g_malloc.tiny)
		g_malloc.tiny = next;
	if (heap == g_malloc.small)
		g_malloc.small = next;
	if (heap == g_malloc.large)
		g_malloc.large = next;
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	pthread_mutex_lock(&g_malloc_mutex);
	// iterate through heaps, checking if block pointer
	// matches ptr
	if (!(find_block(g_malloc.tiny, ptr)))
		if (!(find_block(g_malloc.small, ptr)))
			if (!(find_block(g_malloc.large, ptr)))
			{
				pthread_mutex_unlock(&g_malloc_mutex);
				free_error();
				return ;
			}
	// set block to "not in use"
	set_block_free(g_malloc.heap, g_malloc.block);
	//merge with nearby blocks if possible
	//merge_blocks(g_malloc.block);
	// free heap with munmap if no blocks left
	if (g_malloc.heap->block_amount == g_malloc.heap->blocks_freed)
		remove_heap(g_malloc.heap);
	pthread_mutex_unlock(&g_malloc_mutex);
	// memory leak if not all empty heaps freed?
}
