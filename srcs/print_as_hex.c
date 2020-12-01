/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_as_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:11:54 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 13:16:11 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int	ft_nbrlen_base(size_t n, int base)
{
	int i;

	i = 0;
	while (n || i == 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

static char	base_digit(size_t n, int base)
{
	char	*format;
	int		i;

	format = "0123456789ABCDEF";
	i = n % base;
	if (i < 0)
		i *= -1;
	return (format[i]);
}

void		print_as_hex(size_t num)
{
	int		i;
	int		len;
	char	arr[30];

	len = ft_nbrlen_base(num, 16);
	i = len - 1;
	while (i >= 0)
	{
		arr[i--] = base_digit(num, 16);
		num /= 16;
	}
	write(1, "0x", 2);
	write(1, arr, len);
}

void		print_as_hex_nl(size_t num)
{
	int		i;
	int		len;
	char	arr[30];

	len = ft_nbrlen_base(num, 16);
	i = len - 1;
	while (i >= 0)
	{
		arr[i--] = base_digit(num, 16);
		num /= 16;
	}
	write(1, "0x", 2);
	write(1, arr, len);
	write(1, "\n", 1);
}
