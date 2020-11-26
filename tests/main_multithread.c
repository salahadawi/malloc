/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_multithread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:55:24 by sadawi            #+#    #+#             */
/*   Updated: 2020/11/26 15:11:39 by sadawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include <pthread.h>

void	*thread_malloc(void *arg)
{
	char *ptr;

	(void)arg;
	ptr = malloc(1024);
	return (NULL);
}

int		main(void)
{
	pthread_t	thread_id[100];
	int			i;

	i = 0;
	while (i < 100)
		pthread_create(&thread_id[i++], NULL, thread_malloc, NULL);
	i = 0;
	while (i < 100)
		pthread_join(thread_id[i++], NULL);
	show_alloc_mem();
	return (0);
}
