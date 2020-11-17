/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/17 19:46:25 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>

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
	int				freed;
	struct s_block	*prev;
	struct s_block	*next;

}					t_block;

typedef struct		s_heap
{
	size_t			size;
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

typedef struct		s_heap_and_block
{
	t_heap			*heap;
	t_block			*block;

}					t_heap_and_block;

t_malloc			g_malloc;

#endif
