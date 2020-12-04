/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/04 11:36:36 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t	align_on_bytes(size_t num, size_t alignment)
{
	return ((num + (alignment - 1)) & ~(alignment - 1));
}

t_block			*create_new_block(t_block *ptr, t_block *prev,
									size_t size, t_heap *heap)
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

void			*get_block(t_heap *heap, size_t size)
{
	size_t	i;
	size_t	size_left;
	t_block	*tmp;
	t_block	*prev;

	i = 0;
	size_left = heap->size - sizeof(t_heap);
	tmp = heap_shift(heap);
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
		tmp = tmp->data_size + block_shift(tmp);
		i++;
	}
	if (size + sizeof(t_block) <= size_left)
		return (create_new_block(tmp, prev, size, heap));
	return (NULL);
}

void			*malloc_skip_mutex(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	size = get_block_size(align_on_bytes(size, 16));
	ptr = get_heap(size);
	return (block_shift(ptr));
}

void			*malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_malloc_mutex);
	size = get_block_size(align_on_bytes(size, 16));
	ptr = get_heap(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (block_shift(ptr));
}
