/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/26 15:08:31 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	realloc_error(void)
{
	if (g_malloc.debug_realloc)
	{
		write(2,
		"realloc: *** error: pointer being realloced was not allocated\n", 62);
		exit(1);
	}
}

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	i = 0;
	if (src > dst)
		while (i < len)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
	else
	{
		i = 1;
		while (i <= len)
		{
			((unsigned char*)dst)[len - i] = ((unsigned char*)src)[len - i];
			i++;
		}
	}
	return (dst);
}

static void	*resize_memory(void *ptr, size_t size)
{
	void	*new;
	size_t	len;

	new = malloc_skip_mutex(size);
	len = size < g_malloc.block->data_size ? size : g_malloc.block->data_size;
	ft_memmove(new, ptr, len);
	free(ptr);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (!size && ptr)
	{
		free(ptr);
		return (malloc(1));
	}
	pthread_mutex_lock(&g_malloc_mutex);
	if (!(find_block(g_malloc.tiny, ptr)))
		if (!(find_block(g_malloc.small, ptr)))
			if (!(find_block(g_malloc.large, ptr)))
			{
				pthread_mutex_unlock(&g_malloc_mutex);
				realloc_error();
				return (NULL);
			}
	return (resize_memory(ptr, size));
}
