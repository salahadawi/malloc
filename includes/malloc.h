/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 11:16:14 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

# define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define TINY_HEAP_ALLOCATION_SIZE (4 * getpagesize())
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (16 * getpagesize())
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

# define HEX_PRINT_WIDTH 16

typedef struct			s_block
{
	size_t				data_size;
	int					freed;
	struct s_block		*prev;
	struct s_block		*next;

}						t_block;

typedef struct			s_heap
{
	size_t				size;
	size_t				block_amount;
	size_t				blocks_freed;
	struct s_heap		*prev;
	struct s_heap		*next;

}						t_heap;

typedef struct			s_heap_and_block
{
	t_heap				*heap;
	t_block				*block;

}						t_heap_and_block;

typedef struct			s_malloc
{
	t_heap				*tiny;
	t_heap				*small;
	t_heap				*large;
	t_heap				*heap;
	t_block				*block;
	int					debug_free;
	int					debug_realloc;

}						t_malloc;

extern t_malloc			g_malloc;
extern pthread_mutex_t	g_malloc_mutex;

int						find_block(t_heap *heap, void *ptr);

void					*malloc_skip_mutex(size_t size);

void					free_skip_mutex(void *ptr);

void					show_alloc_mem(void);

void					show_alloc_mem_string(void);

void					show_alloc_mem_hex(void);

void					show_alloc_mem_bytes(void);

void					realloc_error(void);

void					free_error(void);

void					munmap_error(void);

void					mmap_error(void);

#endif
