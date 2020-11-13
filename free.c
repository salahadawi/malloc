/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:17 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/13 18:53:31 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free(void *ptr)
{
	// iterate through heaps, checking if block pointer
	// matches ptr

	// set block to "not in use", merge with nearby blocks
	// if possible

	// free heap with munmap if no blocks left

	// memory leak if not all empty heaps freed?
}
