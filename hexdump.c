/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 18:21:47 by cwu               #+#    #+#             */
/*   Updated: 2018/08/31 18:21:48 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block *g_mem[3];

void	hexdump(void)
{
	int		i;
	int		c;
	t_block	*t;

	i = tiny - 1;
	while (++i < large && (t = g_mem[i]) == g_mem[i])
		while (t)
		{
			if (t->np)
			{
				c = -1;
				while (++c < (int)block_size(i, t))
				{
					if (c != 0 && c % 32 == 0)
						write(1, "\n", 1);
					if (!(c % 32))
						print_address((t_byte*)t + c);
					ft_printf("%.2hhx", *((t_byte*)t + c));
					if (c % 32 != 31)
						write(1, " ", 1);
				}
				write(1, "\n\n", 2);
			}
			t = t->nx;
		}
}
