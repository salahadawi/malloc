/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:11:16 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/01 13:12:10 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_putnbr(size_t n)
{
	int		i;
	size_t	arr[30];

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
	int		i;
	size_t	arr[30];

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
