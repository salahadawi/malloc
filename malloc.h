/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/13 17:16:50 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft/includes/libft.h"
# include <sys/mman.h>

//might need to change to constants ???

# define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (16 * getpagesize())
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

typedef struct		s_block
{
	size_t			data_size;
	struct s_block	*prev;
	struct s_block	*next;

}					t_block;

typedef struct		s_heap
{
	size_t			size;
	size_t			size_available;
	size_t			block_amount;
	struct s_heap	*prev;
	struct s_heap	*next;

}					t_heap;

typedef struct		s_malloc
{
	t_heap			*tiny;
	t_heap			*small;
	t_heap			*large;

}					t_malloc;

t_malloc			g_malloc;

#endif
