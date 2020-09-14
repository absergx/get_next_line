/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:06:32 by memilio           #+#    #+#             */
/*   Updated: 2020/07/10 15:37:04 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == src)
		return (dst);
	while (n > 0)
	{
		--n;
		((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	}
	return (dst);
}

int			gigalloc(t_gnl_container *container, int f)
{
	t_gnl_element	*tmp;
	int				i;

	i = 0;
	if (!f && !(tmp = (t_gnl_element *)malloc((sizeof(t_gnl_element) *
			(container->size)))))
		return (0);
	else if (f)
	{
		if (!(tmp = (t_gnl_element *)malloc(sizeof(t_gnl_element) *
			(container->size * 2))))
			return (0);
		while (i < container->size)
		{
			((t_gnl_element *)tmp)[i] = (container->table)[i];
			i++;
		}
		free(container->table);
		container->size *= 2;
	}
	container->table = tmp;
	while (i < container->size)
		((container->table)[i++]).init = 0;
	return (1);
}

int			container_initialize(t_gnl_container *container, int f, int fd)
{
	if (!container->init && !f)
	{
		container->init = 1;
		container->size = 4;
		container->opened = 0;
		if (!(gigalloc(container, 0)))
			return (0);
	}
	while (container->init && fd >= container->size)
	{
		if (!(gigalloc(container, 1)))
			return (0);
	}
	if (f && !((container->table)[fd].init))
	{
		(container->table)[fd].init = 1;
		(container->table)[fd].reached = 0;
		(container->table)[fd].fd = fd;
		(container->table)[fd].byte_read = 0;
		(container->table)[fd].offset = BUFFER_SIZE;
		(container->table)[fd].surplus = NULL;
		(container->table)[fd].surplus_len = 0;
		container->opened += 1;
	}
	return (1);
}

static int	check_force_exit(t_gnl_container *container)
{
	int	i;

	i = 0;
	while (i < container->size)
	{
		if ((container->table[i]).init && (container->table[i]).surplus)
			free((container->table[i]).surplus);
		i++;
	}
	free(container->table);
	container->init = 0;
	return (-1);
}

int			check_return(t_gnl_element *el, t_gnl_container *container, int ret)
{
	if (el && (((!el->byte_read || (el->reached && el->fd)) && ret == 0) ||
		(ret == -1 && el->byte_read == -1)))
	{
		if (el->reached == -1)
		{
			ret = -1;
			if (el->surplus != NULL)
				free(el->surplus);
		}
		el->init = 0;
		container->opened -= 1;
		if (container->opened == 0)
		{
			free(container->table);
			container->init = 0;
		}
		return (ret);
	}
	else if (!el && ret == -1)
		return (check_force_exit(container));
	return (1);
}
