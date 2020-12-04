/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_heaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:15:09 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/04 11:36:36 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	print_heap_size(t_heap *heap)
{
	if (heap && heap == g_malloc.tiny)
		write(1, "TINY : ", 7);
	else if (heap && heap == g_malloc.small)
		write(1, "SMALL : ", 8);
	else if (heap && heap == g_malloc.large)
		write(1, "LARGE : ", 8);
	else
		return ;
	print_as_hex_nl((size_t)heap);
}

void	print_heaps(t_heap *heap)
{
	t_block *block;
	size_t	i;
	size_t	total_size;
	size_t	heap_num;

	print_heap_size(heap);
	heap_num = 1;
	while (heap)
	{
		i = 0;
		total_size = 0;
		block = heap_shift(heap);
		write(1, "HEAP NUMBER: ", 13);
		ft_putnbr_nl(heap_num);
		while (i++ < heap->block_amount)
		{
			total_size += print_block(block);
			block = block_shift(block) + block->data_size;
		}
		write(1, "Total :", 7);
		ft_putnbr_nl(total_size);
		heap = heap->next;
		heap_num++;
	}
}

void	print_heaps_strings(t_heap *heap)
{
	t_block *block;
	size_t	i;
	size_t	total_size;
	size_t	heap_num;

	print_heap_size(heap);
	heap_num = 1;
	while (heap)
	{
		i = 0;
		total_size = 0;
		block = heap_shift(heap);
		write(1, "HEAP NUMBER: ", 13);
		ft_putnbr_nl(heap_num);
		while (i++ < heap->block_amount)
		{
			total_size += print_block_string(block);
			block = block_shift(block) + block->data_size;
		}
		write(1, "Total :", 7);
		ft_putnbr_nl(total_size);
		heap = heap->next;
		heap_num++;
	}
}

void	print_heaps_bytes(t_heap *heap)
{
	t_block *block;
	size_t	i;
	size_t	total_size;
	size_t	heap_num;

	print_heap_size(heap);
	heap_num = 1;
	while (heap)
	{
		i = 0;
		total_size = 0;
		block = heap_shift(heap);
		write(1, "HEAP NUMBER: ", 13);
		ft_putnbr_nl(heap_num);
		while (i++ < heap->block_amount)
		{
			total_size += print_block_bytes(block);
			block = block_shift(block) + block->data_size;
		}
		write(1, "Total :", 7);
		ft_putnbr_nl(total_size);
		heap = heap->next;
		heap_num++;
	}
}

void	print_heaps_hex(t_heap *heap)
{
	t_block *block;
	size_t	i;
	size_t	total_size;
	size_t	heap_num;

	print_heap_size(heap);
	heap_num = 1;
	while (heap)
	{
		i = 0;
		total_size = 0;
		block = heap_shift(heap);
		write(1, "HEAP NUMBER: ", 13);
		ft_putnbr_nl(heap_num);
		while (i++ < heap->block_amount)
		{
			total_size += print_block_hex(block);
			block = block_shift(block) + block->data_size;
		}
		write(1, "Total :", 7);
		ft_putnbr_nl(total_size);
		heap = heap->next;
		heap_num++;
	}
}
