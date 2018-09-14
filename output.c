/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 16:40:03 by cwu               #+#    #+#             */
/*   Updated: 2018/08/30 16:40:04 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define N 30

t_block *g_mem[3];
pthread_mutex_t g_lock;

void		print_address(void *ptr)
{
	uintptr_t	n;
	char		str[10];
	char		*hex;
	int			i;

	write(1, "0x", 2);
	hex = "0123456789abcdef";
	n = (uintptr_t)ptr;
	str[9] = '\0';
	i = 9;
	while (--i >= 0)
	{
		str[i] = hex[n & 15];
		n >>= 4;
	}
	write(1, str, 9);
}

static void	print_header(int i, t_block *t)
{
	write(1, WHITE, ft_strlen(WHITE));
	if (i == tiny)
		write(1, "TINY BLOCK: ", 13);
	else if (i == small)
		write(1, "SMALL BLOCK: ", 14);
	else
		write(1, "LARGE BLOCK: ", 14);
	print_address(t);
	write(1, "\n", 1);
}

static void	print_line(t_block *t, int i, int *total)
{
	if (t->np)
		print_header(i, t);
	if (t->oc)
	{
		write(1, ORANGE, ft_strlen(ORANGE));
		*total += t->size;
	}
	else
		write(1, LG, ft_strlen(LG));
	write(1, "\t", 1);
	print_address((t_byte*)t + HSIZE);
	write(1, " - ", 3);
	print_address(ADDR(t) + t->size);
	write(1, " : ", 3);
	ft_putnbr(t->size);
	write(1, " bytes\n", 7);
}

void		show_alloc_mem(void)
{
	t_block	*t;
	int		i;
	int		total;

	pthread_mutex_lock(&g_lock);
	total = 0;
	i = tiny - 1;
	while (++i <= large)
	{
		t = g_mem[i];
		while (t)
		{
			print_line(t, i, &total);
			t = t->nx;
		}
	}
	ft_putstr(WHITE);
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putchar('\n');
	pthread_mutex_unlock(&g_lock);
}
