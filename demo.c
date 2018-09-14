/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 21:55:51 by cwu               #+#    #+#             */
/*   Updated: 2018/08/30 21:55:53 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define N 42

t_block *g_mem[3];

void	new_line(int i)
{
	if (i != 0 && i % 64 == 0)
		printf("\n");
	if (!(i % 64))
	{
		printf(WHITE);
		printf("%.8X ", i);
	}
}

void	print_memory(int i, t_block *memory, int header, int size)
{
	t_block *t;

	t = memory;
	while (++i < 4096)
	{
		new_line(i);
		if (!size)
		{
			t = t->nx;
			header = HSIZE;
			size = t->size;
		}
		if (header && header-- >= -17)
			printf(t->oc ? RED : GREEN);
		else
		{
			printf(t->oc ? ORANGE : LG);
			size--;
		}
		printf("%.2X", ((t_byte*)memory)[i]);
		if (i % 64 != 63)
			printf(" ");
	}
}

void	hexdumper(t_block *memory)
{
	printf("\e[1J");
	print_memory(-1, memory, HSIZE, memory->size);
	printf("\n");
	usleep(500000);
}

void	demo_loop(t_byte *ptr[N], bool u[N], int i)
{
	unsigned int r;
	unsigned int j;

	while (++i < N)
		if (u[i] == false)
		{
			r = rand() % 100;
			ptr[i] = (t_byte*)malloc(r);
			j = -1;
			while (++j < r)
				ptr[i][j] = 0x88;
			u[i] = true;
		}
	hexdumper(g_mem[0]);
	i = -1;
	while (++i < N)
		if (u[i] && !(rand() % 5))
		{
			free(ptr[i]);
			u[i] = false;
		}
	hexdumper(g_mem[0]);
}

int		main(void)
{
	t_byte	*ptr[N];
	bool	u[N];
	int		i;

	srand(time(0));
	i = -1;
	while (++i < N)
	{
		u[i] = false;
		ptr[i] = NULL;
	}
	while (1)
		demo_loop(ptr, u, -1);
	return (0);
}
