/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:21:40 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/13 12:20:07 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft/includes/libft.h"
# include <sys/mman.h>

typedef struct	s_malloc
{
	t_heap
}				t_malloc;

t_malloc		*g_malloc;

#endif
