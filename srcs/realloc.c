/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/24 15:19:48 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	realloc_error(void)
{
	write(2, "realloc: *** error: pointer being realloced was not allocated\n", 62);
	exit(1);
}

// int		attempt_resize(void *ptr, size_t size)
// {

// }

void	*ft_memmove(void *dst, const void *src, size_t len)
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


void	*tmp_realloc(void *ptr, size_t size)
{
	void	*new;
	size_t	len;

	new = malloc(size);
	len = size < g_malloc.block->data_size ? size : g_malloc.block->data_size;
	ft_memmove(new, ptr, len);
	free(ptr);
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
	pthread_mutex_unlock(&g_malloc_mutex);
	return (tmp_realloc(ptr, size));
	// if (attempt_resize(ptr, size))
	// 	return (ptr);
	// free(ptr);
	return (ptr);
}
