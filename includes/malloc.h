/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/02 13:14:46 by sadawi           ###   ########.fr       */
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

int						ft_isprint(int c);

void					ft_putchar(int c);

void					ft_putnbr(size_t n);

void					ft_putnbr_nl(size_t n);

size_t					ft_strlen(char *str);

size_t					get_heap_size(size_t size);

size_t					get_block_size(size_t size);

size_t					calculate_large_heap_size(size_t size);

void					*get_heap(size_t size);

t_heap					*create_new_heap(t_heap *prev, size_t size);

void					store_head(t_heap *new_heap, size_t size);

void					print_as_hex(size_t num);

void					print_as_hex_nl(size_t num);

size_t					print_block(t_block *block);

size_t					print_block_string(t_block *block);

size_t					print_block_bytes(t_block *block);

size_t					print_block_hex(t_block *block);

void					print_heaps(t_heap *heap);

void					print_heaps_strings(t_heap *heap);

void					print_heaps_bytes(t_heap *heap);

void					print_heaps_hex(t_heap *heap);

void					write_data_bytes(unsigned char *data, size_t data_size);

void					write_data_ascii(unsigned char *data, int i);

void					write_data_hex(unsigned char *data, size_t data_size);

void					*get_block(t_heap *heap, size_t size);

t_block					*create_new_block(t_block *ptr, t_block *prev,
									size_t size, t_heap *heap);

#endif
