/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 01:01:23 by cwu               #+#    #+#             */
/*   Updated: 2018/08/30 01:01:24 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *g_mem[3] = {NULL, NULL, NULL};
pthread_mutex_t g_lock;

void	*put_in_gap(t_block *t, t_block **pt2, size_t size)
{
	t_block	*new;

	while (t)
	{
		if (!t->oc && t->size >= (unsigned int)size)
		{
			if (t->size - size > HSIZE)
			{
				new = (t_block*)(ADDR(t) + size);
				ft_bzero(new, sizeof(t_block*));
				new->size = t->size - size - HSIZE;
				new->nx = t->nx;
				t->size = size;
				t->nx = new;
			}
			t->oc = 1;
			return (ADDR(t));
		}
		*pt2 = t;
		t = t->nx;
	}
	return (NULL);
}

void	*new_page(int i, size_t size, t_block *t2)
{
	t_block	*t;
	t_block	*new;
	int		l;

	l = page_size(i, size);
	new = (t_block*)mmap(0, l, DBMMAP);
	ft_bzero((t_byte*)new, l);
	new->size = size;
	new->np = 1;
	new->oc = 1;
	new->nx = NULL;
	if (t2)
		t2->nx = new;
	else
		g_mem[i] = new;
	if (i < large)
	{
		t = (t_block*)(ADDR(new) + size);
		new->nx = t;
		t->size = page_size(i, 0) - 2 * HSIZE - size;
		t->oc = 0;
		t->np = 0;
		t->nx = NULL;
	}
	return (ADDR(new));
}

void	*malloc(size_t size)
{
	t_block	*t;
	t_block	*t2;
	t_byte	*p;
	int		i;

	if (size == 0)
		return (NULL);
	pthread_mutex_lock(&g_lock);
	if (size <= TINY - HSIZE)
		i = tiny;
	else if (size <= SMALL - HSIZE)
		i = small;
	else
		i = large;
	t = g_mem[i];
	t2 = t;
	p = put_in_gap(t, &t2, size);
	if (!p)
		p = new_page(i, size, t2);
	pthread_mutex_unlock(&g_lock);
	return (void*)p;
}

void	free(void *ptr)
{
	t_block	*t;
	t_block	*t2;
	int		i;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_lock);
	t2 = NULL;
	t = find_malloc((t_byte*)ptr, &t2, &i);
	if (i < large)
		empty_block(&t, &t2);
	if ((i == tiny && t->size == TINY * NT - HSIZE) ||
		(i == small && t->size == SMALL * NS - HSIZE) || i == large)
	{
		if (g_mem[i] == t)
			g_mem[i] = t->nx;
		else if (t2)
			t2->nx = t->nx;
		munmap((t_byte*)t, block_size(i, t));
	}
	pthread_mutex_unlock(&g_lock);
	return ;
}
