/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:50:37 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 13:37:28 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_malloc_mutex);
	print_heaps(g_malloc.tiny);
	print_heaps(g_malloc.small);
	print_heaps(g_malloc.large);
	pthread_mutex_unlock(&g_malloc_mutex);
}

void	show_alloc_mem_string(void)
{
	pthread_mutex_lock(&g_malloc_mutex);
	print_heaps_strings(g_malloc.tiny);
	print_heaps_strings(g_malloc.small);
	print_heaps_strings(g_malloc.large);
	pthread_mutex_unlock(&g_malloc_mutex);
}

void	show_alloc_mem_bytes(void)
{
	pthread_mutex_lock(&g_malloc_mutex);
	print_heaps_bytes(g_malloc.tiny);
	print_heaps_bytes(g_malloc.small);
	print_heaps_bytes(g_malloc.large);
	pthread_mutex_unlock(&g_malloc_mutex);
}

void	show_alloc_mem_hex(void)
{
	pthread_mutex_lock(&g_malloc_mutex);
	print_heaps_hex(g_malloc.tiny);
	print_heaps_hex(g_malloc.small);
	print_heaps_hex(g_malloc.large);
	pthread_mutex_unlock(&g_malloc_mutex);
}
