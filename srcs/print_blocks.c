/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:14:06 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 13:15:00 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t	print_block(t_block *block)
{
	if (block->freed)
		return (0);
	print_as_hex((size_t)BLOCK_SHIFT(block));
	write(1, " - ", 3);
	print_as_hex((size_t)BLOCK_SHIFT(block) + block->data_size);
	write(1, ": ", 2);
	ft_putnbr(block->data_size);
	write(1, " bytes\n", 7);
	return (block->data_size);
}

size_t	print_block_string(t_block *block)
{
	if (block->freed)
		return (0);
	print_as_hex((size_t)BLOCK_SHIFT(block));
	write(1, " - ", 3);
	print_as_hex((size_t)BLOCK_SHIFT(block) + block->data_size);
	write(1, ": ", 2);
	ft_putnbr(block->data_size);
	write(1, " bytes\n", 7);
	write(1, BLOCK_SHIFT(block), block->data_size);
	write(1, "\n", 1);
	return (block->data_size);
}

size_t	print_block_bytes(t_block *block)
{
	if (block->freed)
		return (0);
	print_as_hex((size_t)BLOCK_SHIFT(block));
	write(1, " - ", 3);
	print_as_hex((size_t)BLOCK_SHIFT(block) + block->data_size);
	write(1, ": ", 2);
	ft_putnbr(block->data_size);
	write(1, " bytes\n", 7);
	write_data_bytes(BLOCK_SHIFT(block), block->data_size);
	write(1, "\n", 1);
	return (block->data_size);
}

size_t	print_block_hex(t_block *block)
{
	if (block->freed)
		return (0);
	print_as_hex((size_t)BLOCK_SHIFT(block));
	write(1, " - ", 3);
	print_as_hex((size_t)BLOCK_SHIFT(block) + block->data_size);
	write(1, ": ", 2);
	ft_putnbr(block->data_size);
	write(1, " bytes\n", 7);
	write_data_hex(BLOCK_SHIFT(block), block->data_size);
	write(1, "\n", 1);
	return (block->data_size);
}
