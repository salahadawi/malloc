/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/19 18:29:17 by sadawi           ###   ########.fr       */
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
	size_t			blocks_freed;
	struct s_heap	*prev;
	struct s_heap	*next;

}					t_heap;

typedef struct		s_heap_and_block
{
	t_heap			*heap;
	t_block			*block;

}					t_heap_and_block;

typedef struct		s_malloc
{
	t_heap			*tiny;
	t_heap			*small;
	t_heap			*large;

	//tmp, probably not allowed
	t_heap			*heap;
	t_block			*block;

}					t_malloc;

t_malloc			g_malloc;

void				show_alloc_mem(void);

void				show_alloc_mem_string(void);

int					find_block(t_heap *heap, void *ptr);

#endif
