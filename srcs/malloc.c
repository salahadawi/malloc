/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/19 15:02:46 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

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
	return (align_on_bytes(size + sizeof(t_block) + sizeof(t_heap), getpagesize()));
}

size_t	get_block_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY_BLOCK_SIZE);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL_BLOCK_SIZE);
	return (size);
}

size_t	get_block_size_create(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY_BLOCK_SIZE);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL_BLOCK_SIZE);
	return (size - sizeof(t_block));
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
	new_heap->blocks_freed = 0;
	if (prev)
		prev->next = new_heap;
	else
		store_head(new_heap, size);
	return (new_heap);
}

t_block	*create_new_block(t_block *ptr, t_block *prev, size_t size, t_heap *heap)
{
	size = get_block_size(size);
	ptr->data_size = size;
	ptr->freed = 0;
	ptr->next = NULL;
	ptr->prev = prev;
	if (prev)
		prev->next = ptr;
	heap->block_amount++;
	return (ptr);
}

t_heap	*get_heap_list(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (g_malloc.tiny);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (g_malloc.small);
	return (g_malloc.large);
}

void	*get_block2(t_heap *heap, size_t size)
{
	size_t	i;
	size_t	size_left;
	t_block	*tmp;
	t_block	*prev;

	i = 0;
	size_left = heap->size - sizeof(t_heap);
	tmp = HEAP_SHIFT(heap);
	prev = NULL;
	while (i != heap->block_amount)
	{
		if (tmp->freed && size <= tmp->data_size)
		{
			tmp->freed = 0;
			heap->blocks_freed--;
			return (tmp);
		}
		size_left -= tmp->data_size + sizeof(t_block);
		prev = tmp;
		tmp = tmp->data_size + BLOCK_SHIFT(tmp);
		i++;
	}
	if (size + sizeof(t_block) <= size_left)
		return (create_new_block(tmp, prev, size, heap));
	return (NULL);
}

void	*get_heap(size_t size)
{
	t_heap	*ptr;
	t_block	*block;

	ptr = get_heap_list(size);
	while (1)
	{
		if (ptr && (block = get_block2(ptr, size)))
			return (block);
		if (!ptr || !ptr->next)
		{
			ptr = create_new_heap(ptr, size);
			return (create_new_block(HEAP_SHIFT(ptr), NULL, size, ptr));
		}
		ptr = ptr->next;
		// if (ptr->biggest_block_available >= size + sizeof(t_block))
		// 	return (ptr);
		// if (!ptr->next)
		// 	return (create_new_heap(ptr, size));
		// ptr = ptr->next;
	}
}

// void	*get_block(t_heap *heap, size_t size)
// {
// 	t_block	*ptr;
// 	t_block	*prev;
// 	size_t	i;

// 	i = 0;
// 	prev = NULL;
// 	ptr = HEAP_SHIFT(heap);
// 	while (1)
// 	{
// 		if (i == heap->block_amount)
// 		{
// 			ptr = create_new_block(ptr, prev, size);
// 			heap->block_amount++;
// 			return (ptr);
// 		}
// 		prev = ptr;
// 		ptr = ptr->data_size + BLOCK_SHIFT(ptr);
// 		i++;
// 	}
// }

void	*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	size = get_block_size(align_on_bytes(size, 16));
	ptr = get_heap(size);
	//ptr = get_block(ptr, size);
	return (BLOCK_SHIFT(ptr));
}
