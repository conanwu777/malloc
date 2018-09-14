/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:49:23 by cwu               #+#    #+#             */
/*   Updated: 2018/08/31 15:49:24 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <stdbool.h>
# include <sys/mman.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

# define RED "\e[1;38;2;225;20;20m"
# define ORANGE "\e[1;38;2;255;120;10m"
# define YELLO "\e[1;38;2;255;200;0m"
# define GREEN "\e[1;38;2;0;170;101m"
# define LG "\e[1;38;2;167;244;66m"
# define BLUE "\e[1;38;2;50;150;250m"
# define PURPLE "\e[1;38;2;150;75;255m"
# define WHITE "\e[1;38;2;255;250;232m"

# define PAGESIZE getpagesize()
# define DBMMAP PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0
# define TINY 4096
# define NT 128
# define SMALL 1064960
# define NS 128
# define HSIZE sizeof(t_block)
# define ADDR(X) (t_byte*)(X) + HSIZE

enum
{
	tiny,
	small,
	large
};

typedef unsigned char	t_byte;

typedef struct			s_block
{
	bool			oc;
	bool			np;
	unsigned int	size;
	struct s_block	*nx;
}						t_block;

size_t					block_size(int i, t_block *t);
void					free(void *ptr);
t_block					*find_malloc(void *ptr, t_block **pt2, int *pi);
void					empty_block(t_block **pt, t_block **pt2);
int						page_size(int i, size_t size);
void					*realloc(void *ptr, size_t size);
void					*malloc(size_t size);
void					show_alloc_mem();
void					print_address(void *ptr);
void					*new_page(int i, size_t size, t_block *t2);
void					*put_in_gap(t_block *t, t_block **pt2, size_t size);
void					hexdump(void);

extern t_block *g_mem[3];
extern pthread_mutex_t g_lock;

#endif
