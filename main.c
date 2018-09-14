/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 01:01:31 by cwu               #+#    #+#             */
/*   Updated: 2018/08/30 01:01:33 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define N 50

bool	random_malloc(int max, t_byte **ptr)
{
	unsigned int	r;
	int				j;

	r = rand() % max;
	*ptr = (t_byte*)malloc(r);
	j = 0;
	while (j < (int)r)
	{
		(*ptr)[j] = 0x88;
		j++;
	}
	return (true);
}

bool	random_free(int ratio, t_byte **ptr)
{
	if (!(rand() % ratio))
	{
		free(*ptr);
		return (false);
	}
	return (true);
}

bool	random_realloc(int max, t_byte **ptr)
{
	unsigned int r;

	r = rand() % max;
	*ptr = (t_byte*)realloc(*ptr, r);
	if (!*ptr)
		return (false);
	return (true);
}

void	output(void)
{
	ft_putstr("\e[1J");
	show_alloc_mem();
	usleep(500000);
}

int		main(void)
{
	t_byte	*ptr[N];
	bool	u[N];
	int		i;

	srand(time(0));
	i = -1;
	while (++i < N)
		u[i] = false;
	while (1)
	{
		i = -1;
		while (++i < N)
			u[i] = (!u[i] ? random_malloc(1200000, &(ptr[i])) : true);
		i = rand() % N;
		u[i] = (u[i] ? random_realloc(1200000, &(ptr[i])) : false);
		i = -1;
		while (++i < N)
			u[i] = (u[i] ? random_free(3, &(ptr[i])) : false);
		output();
	}
	return (0);
}
