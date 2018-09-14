/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:24:01 by cwu               #+#    #+#             */
/*   Updated: 2018/08/31 15:24:03 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *g_mem[3];
pthread_mutex_t g_lock;

static void	*malunloc(size_t size)
{
	t_block	*t;
	t_block	*t2;
	t_byte	*p;
	int		i;

	if (size == 0)
		return (NULL);
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
	return (void*)p;
}

static void	freeunloc(void *ptr)
{
	t_block	*t;
	t_block	*t2;
	int		i;

	if (!ptr)
		return ;
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
	return ;
}

static void	*expand(t_block *t, size_t size)
{
	t_block *t2;
	t_block *t3;
	int		tsize;

	if ((unsigned int)size < t->size + t->nx->size)
	{
		tsize = t->nx->size;
		t3 = t->nx->nx;
		t2 = (t_block*)(ADDR(t) + size);
		ft_bzero(t2, sizeof(t_block));
		t2->size = t->size + tsize - size;
		t->size = size;
		t2->nx = t3;
		t->nx = t2;
	}
	else
	{
		t->nx = t->nx->nx;
		t->size += t->nx->size + HSIZE;
	}
	return ((void*)ADDR(t));
}

static void	*unlock_return(void *ptr)
{
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*t;
	int		i;

	if (!ptr)
		return (malloc(size));
	if (!size)
		free(ptr);
	pthread_mutex_lock(&g_lock);
	if (!size || !(t = find_malloc(ptr, NULL, &i)))
		return (unlock_return(NULL));
	if ((unsigned int)size <= t->size)
		return (unlock_return(ptr));
	if (t->nx && !t->nx->oc && !t->nx->np &&
		(unsigned int)size < t->size + t->nx->size + (unsigned int)HSIZE)
		ptr = expand(t, size);
	else
	{
		ptr = malunloc(size);
		ft_memcpy(ptr, ADDR(t), t->size);
		freeunloc(ADDR(t));
	}
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
