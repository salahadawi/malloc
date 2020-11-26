/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:57:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/26 15:58:40 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	realloc_error(void)
{
	if (g_malloc.debug_realloc)
	{
		write(2,
		"realloc: *** error: pointer being realloced was not allocated\n", 62);
		exit(1);
	}
}

void	free_error(void)
{
	if (g_malloc.debug_free)
	{
		write(2, "malloc: *** error: pointer being freed was not allocated\n",
		57);
		exit(1);
	}
}

void	munmap_error(void)
{
	write(2, "munmap: *** error: address allocation deletion failed\n", 54);
	exit(1);
}

void	mmap_error(void)
{
	write(2, "mmap: *** error: address allocation failed\n", 49);
	exit(1);
}

