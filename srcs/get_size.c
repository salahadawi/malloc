/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:23:07 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 13:23:46 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t	get_heap_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY_HEAP_ALLOCATION_SIZE);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL_HEAP_ALLOCATION_SIZE);
	return (calculate_large_heap_size(size));
}

size_t	get_block_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY_BLOCK_SIZE);
	if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL_BLOCK_SIZE);
	return (size);
}

size_t	calculate_large_heap_size(size_t size)
{
	int multiple;

	multiple = getpagesize() / ((size + sizeof(t_block)) + sizeof(t_heap));
	multiple++;
	return (multiple * (size + sizeof(t_block)) + sizeof(t_heap));
}
