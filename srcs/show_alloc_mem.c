/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:50:37 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/19 10:57:37 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putnbr(size_t n)
{
	int i;
	size_t arr[30];

	i = 0;
	if (n == 0)
		ft_putchar('0');
	while (n)
	{
		arr[i] = n % 10;
		n /= 10;
		i++;
	}
	i--;
	while (i >= 0)
		ft_putchar(arr[i--] + '0');
}

void	ft_putnbr_nl(size_t n)
{
	int i;
	size_t arr[30];

	i = 0;
	if (n == 0)
		ft_putchar('0');
	while (n)
	{
		arr[i] = n % 10;
		n /= 10;
		i++;
	}
	i--;
	while (i >= 0)
		ft_putchar(arr[i--] + '0');
	ft_putchar('\n');
}

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
	ft_putnbr_nl((size_t)heap);
}

size_t	print_block(t_block *block)
{
	ft_putnbr((size_t)BLOCK_SHIFT(block));
	write(1, " - ", 3);
	ft_putnbr((size_t)BLOCK_SHIFT(block) + block->data_size);
	write(1, ": ", 2);
	ft_putnbr(block->data_size);
	write(1, " bytes\n", 7);
	return (block->data_size);
}

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

size_t	print_block_string(t_block *block)
{
	ft_putnbr((size_t)BLOCK_SHIFT(block));
	write(1, " - ", 3);
	ft_putnbr((size_t)BLOCK_SHIFT(block) + block->data_size);
	write(1, ": ", 2);
	ft_putnbr(block->data_size);
	write(1, " bytes | string: ", 7);
	write(1, BLOCK_SHIFT(block), ft_strlen(BLOCK_SHIFT(block)));
	write(1, "\n", 1);
	return (block->data_size);
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
		block = HEAP_SHIFT(heap);
		write(1, "HEAP NUMBER: ", 13);
		ft_putnbr_nl(heap_num);
		while (i++ < heap->block_amount)
		{
			total_size += print_block(block);
			block = BLOCK_SHIFT(block) + block->data_size;
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
		block = HEAP_SHIFT(heap);
		write(1, "HEAP NUMBER: ", 13);
		ft_putnbr_nl(heap_num);
		while (i++ < heap->block_amount)
		{
			total_size += print_block_string(block);
			block = BLOCK_SHIFT(block) + block->data_size;
		}
		write(1, "Total :", 7);
		ft_putnbr_nl(total_size);
		heap = heap->next;
		heap_num++;
	}
}

void	show_alloc_mem(void)
{
	print_heaps(g_malloc.tiny);
	print_heaps(g_malloc.small);
	print_heaps(g_malloc.large);
}

void	show_alloc_mem_string(void)
{
	print_heaps_strings(g_malloc.tiny);
	print_heaps_strings(g_malloc.small);
	print_heaps_strings(g_malloc.large);
}