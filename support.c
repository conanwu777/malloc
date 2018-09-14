/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 01:01:42 by cwu               #+#    #+#             */
/*   Updated: 2018/08/30 01:01:44 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	block_size(int i, t_block *t)
{
	if (i == tiny)
		return (PAGESIZE * ((TINY * NT + PAGESIZE - 1) / PAGESIZE));
	else if (i == small)
		return (PAGESIZE * ((SMALL * NS + PAGESIZE - 1) / PAGESIZE));
	else
		return (t->size + HSIZE);
}

void	empty_block(t_block **pt, t_block **pt2)
{
	if (*pt2 && !(*pt2)->oc && !(*pt)->np)
	{
		if ((*pt)->nx && !(*pt)->nx->oc && !(*pt)->nx->np)
		{
			(*pt2)->size += (*pt)->nx->size + HSIZE;
			(*pt2)->nx = (*pt)->nx->nx;
		}
		else
			(*pt2)->nx = (*pt)->nx;
		(*pt2)->size += (*pt)->size + HSIZE;
		(*pt) = (*pt2);
	}
	else
	{
		(*pt)->oc = 0;
		if ((*pt)->nx && !(*pt)->nx->oc && !(*pt)->nx->np)
		{
			(*pt)->size += (*pt)->nx->size + HSIZE;
			(*pt)->nx = (*pt)->nx->nx;
		}
	}
}

int		page_size(int i, size_t size)
{
	if (i == tiny)
		return (PAGESIZE * ((TINY * NT + PAGESIZE - 1) / PAGESIZE));
	else if (i == small)
		return (PAGESIZE * ((SMALL * NS + PAGESIZE - 1) / PAGESIZE));
	else
		return (size + HSIZE);
}

t_block	*find_malloc(void *ptr, t_block **pt2, int *pi)
{
	t_block	*t;

	*pi = tiny - 1;
	while (++(*pi) <= large)
	{
		t = g_mem[*pi];
		if (pt2)
			*pt2 = t;
		while (t)
		{
			if (t->oc && ADDR(t) == ptr)
				return (t);
			if (pt2)
				*pt2 = t;
			t = t->nx;
		}
	}
	return (NULL);
}
