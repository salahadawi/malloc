/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 15:11:33 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/24 15:17:58 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	enable_free_errors(void)
{
	g_malloc.debug_free = 1;
}

void	disable_free_errors(void)
{
	g_malloc.debug_free = 0;
}

void	enable_realloc_errors(void)
{
	g_malloc.debug_realloc = 1;
}

void	disable_realloc_errors(void)
{
	g_malloc.debug_realloc = 0;
}
