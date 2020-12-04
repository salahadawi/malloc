/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:34:08 by sadawi            #+#    #+#             */
/*   Updated: 2020/12/04 11:36:36 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*heap_shift(void *start)
{
	return (start + sizeof(t_heap));
}

void	*block_shift(void *start)
{
	return (start + sizeof(t_block));
}
