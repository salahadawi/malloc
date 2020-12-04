/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_get_heap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:26:58 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/04 11:50:47 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_heap	*get_heap_list(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (g_malloc.tiny);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (g_malloc.small);
	return (g_malloc.large);
}

void			*get_heap(size_t size)
{
	t_heap	*ptr;
	t_block	*block;

	ptr = get_heap_list(size);
	while (1)
	{
		if (ptr && (block = get_block(ptr, size)))
			return (block);
		if (!ptr || !ptr->next)
		{
			ptr = create_new_heap(ptr, size);
			return (create_new_block(heap_shift(ptr), NULL, size, ptr));
		}
		ptr = ptr->next;
	}
}

t_heap			*create_new_heap(t_heap *prev, size_t size)
{
	t_heap	*new_heap;
	size_t	heap_size;

	heap_size = get_heap_size(size);
	new_heap = (t_heap*)mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0);
	new_heap == MAP_FAILED ? mmap_error() : 0;
	new_heap->prev = prev;
	new_heap->next = NULL;
	new_heap->size = heap_size;
	new_heap->block_amount = 0;
	new_heap->blocks_freed = 0;
	if (prev)
		prev->next = new_heap;
	else
		store_head(new_heap, size);
	return (new_heap);
}

void			store_head(t_heap *new_heap, size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		g_malloc.tiny = new_heap;
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		g_malloc.small = new_heap;
	else
		g_malloc.large = new_heap;
}
