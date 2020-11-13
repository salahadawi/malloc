/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/13 17:52:30 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align_on_bytes(size_t num, size_t alignment)
{
	return ((num + (alignment - 1)) & ~(alignment - 1));
}

size_t	get_heap_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY_HEAP_ALLOCATION_SIZE);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL_HEAP_ALLOCATION_SIZE);
	return (align_on_bytes(size, getpagesize()));
}

void	store_head(t_heap *new_heap, size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		g_malloc.tiny = new_heap;
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		g_malloc.small = new_heap;
	else
		g_malloc.large = new_heap;
}

t_heap	*create_new_heap(t_heap *prev, size_t size)
{
	t_heap	*new_heap;
	size_t	heap_size;

	heap_size = get_heap_size(size);
	new_heap = (t_heap*)mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0);
	new_heap->prev = prev;
	new_heap->next = NULL;
	new_heap->size = heap_size;
	new_heap->block_amount = 0;
	new_heap->size_available = heap_size - sizeof(t_heap);
	if (prev)
		prev->next = new_heap;
	else
		store_head(new_heap, size);
	return (new_heap);
}

t_heap	*get_heap_list(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (g_malloc.tiny);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (g_malloc.small);
	return (g_malloc.large);
}

void	*get_heap(size_t size)
{
	t_heap *ptr;

	ptr = get_heap_list(size);
	if (!ptr)
		return (create_new_heap(ptr, size));
	while (1)
	{
		if (ptr->size_available >= size + sizeof(t_block))
			return (ptr);
		if (!ptr->next)
			return (create_new_heap(ptr, size));
		ptr = ptr->next;
	}
}

t_block	*create_new_block(t_block *ptr, t_block *prev, size_t size)
{
	ptr->data_size = size;
	ptr->next = NULL;
	ptr->prev = NULL;
	if (prev)
		prev->next = ptr;
	return (ptr);
}

void	*get_block(t_heap *heap, size_t size)
{
	t_block	*ptr;
	t_block	*prev;
	size_t	i;

	i = 0;
	prev = NULL;
	ptr = HEAP_SHIFT(heap);
	while (1)
	{
		if (i == heap->block_amount)
		{
			ptr = create_new_block(ptr, prev, size);
			heap->block_amount++;
			heap->size_available -= size + sizeof(t_block);
			return (ptr);

		}
		prev = ptr;
		ptr = ptr->data_size + BLOCK_SHIFT(ptr);
		i++;
	}
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	size = align_on_bytes(size, 16);
	ptr = get_heap(size);
	ptr = get_block(ptr, size);
	return (BLOCK_SHIFT(ptr));
}
