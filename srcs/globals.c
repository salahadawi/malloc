/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:10:20 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/24 13:39:07 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t	g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

t_malloc		g_malloc;
