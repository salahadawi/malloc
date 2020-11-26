/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:55:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/26 15:13:16 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"
#include <string.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	if (!(str = (char*)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

int g_amount = 100;

int		main(void)
{
	char	*ptr;
	char	*arr[g_amount];
	int		i;

	i = 0;
	while (i < g_amount)
	{
		ptr = malloc(i + 1);
		ft_memset(ptr, 200, i);
		ptr[i] = '\0';
		printf("ptr returned to main - %p, %d\n", ptr, i);
		arr[i] = ptr;
		i++;
	}
	i = 0;
	free(arr[0]);
	show_alloc_mem_hex();
}
