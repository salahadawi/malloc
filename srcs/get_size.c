/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:23:07 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/04 12:33:44 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t	get_heap_size(size_t size)
{
	if (size <= (size_t)g_malloc.tiny_block_size)
		return (g_malloc.tiny_heap_alloc_size);
	if (size <= (size_t)g_malloc.small_block_size)
		return (g_malloc.small_heap_alloc_size);
	return (calculate_large_heap_size(size));
}

size_t	get_block_size(size_t size)
{
	if (size <= (size_t)g_malloc.tiny_block_size)
		return (g_malloc.tiny_block_size);
	if (size <= (size_t)g_malloc.small_block_size)
		return (g_malloc.small_block_size);
	return (size);
}

size_t	calculate_large_heap_size(size_t size)
{
	int multiple;

	multiple = getpagesize() / ((size + sizeof(t_block)) + sizeof(t_heap));
	multiple++;
	return (multiple * (size + sizeof(t_block)) + sizeof(t_heap));
}

void	init_pagesizes(void)
{
	g_malloc.tiny_heap_alloc_size = 4 * getpagesize();
	g_malloc.small_heap_alloc_size = 16 * getpagesize();
	g_malloc.tiny_block_size = g_malloc.tiny_heap_alloc_size / 128;
	g_malloc.small_block_size = g_malloc.small_heap_alloc_size / 128;
}
