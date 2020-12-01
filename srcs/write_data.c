/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:16:33 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 13:16:55 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	write_data_bytes(unsigned char *data, size_t data_size)
{
	size_t	i;

	i = 0;
	while (i < data_size)
	{
		ft_putnbr(data[i++]);
		ft_putchar(' ');
	}
}

void	write_data_ascii(unsigned char *data, int i)
{
	int len;

	len = 0;
	ft_putchar('\t');
	while (len < HEX_PRINT_WIDTH)
	{
		if (ft_isprint(data[i + len]))
			ft_putchar(data[i + len]);
		else
			ft_putchar('.');
		len++;
	}
	ft_putchar('\n');
}

void	write_data_hex(unsigned char *data, size_t data_size)
{
	size_t	i;
	char	*hex;

	hex = "0123456789ABCDEF";
	i = 0;
	while (i < data_size)
	{
		ft_putchar(hex[data[i] / 16]);
		ft_putchar(hex[data[i++] % 16]);
		ft_putchar(' ');
		if (!(i % HEX_PRINT_WIDTH))
			write_data_ascii(data, i - HEX_PRINT_WIDTH);
	}
}
