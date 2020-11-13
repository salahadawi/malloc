/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/13 17:09:05 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	align_on_bytes(size_t *num, size_t alignment)
{
	*num = (*num + (alignment - 1)) & ~(alignment - 1);
}

t_heap	*create_new_heap(t_heap *prev, size_t size)
{
	t_heap	*new_heap;
	size_t	heap_size;

	//replace with different sized heaps
	//if (size)
	(void)size;
		heap_size = TINY_HEAP_ALLOCATION_SIZE;
	new_heap = (t_heap*)mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
	MAP_PRIVATE | MAP_ANON, -1, 0);
	new_heap->prev = prev;
	new_heap->next = NULL;
	new_heap->size = heap_size;
	new_heap->block_amount = 0;
	new_heap->size_available = heap_size - sizeof(t_heap);
	if (prev)
		prev->next = new_heap;
	return (new_heap);
}

//inefficient, iterates twice if allocating new heap
void	*get_heap(size_t size)
{
	t_heap *ptr;

	ptr = g_malloc.tiny;
	while (1)
	{
		if (!ptr || !ptr->next)
			return (create_new_heap(ptr, size));
		if (ptr->size_available >= size + sizeof(t_block))
			return (ptr);
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
		ptr = ptr->next;
		i++;
	}
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	align_on_bytes(&size, 16);
	ptr = get_heap(size);
	ptr = get_block(ptr, size);
	return (BLOCK_SHIFT(ptr));
}
