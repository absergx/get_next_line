/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:05:54 by memilio           #+#    #+#             */
/*   Updated: 2020/07/10 15:40:55 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_store(t_gnl_element *el, int f)
{
	char	*tmp;
	char	c;

	c = el->buffer[el->offset];
	el->offset += 1;
	if (!(tmp = (char *)malloc(sizeof(char) * (el->surplus_len + 1)))
			&& (el->reached = -1))
		return (NULL);
	if (el->surplus != NULL)
	{
		ft_memcpy(tmp, el->surplus, el->surplus_len);
		free(el->surplus);
	}
	if (c == '\n' || f)
	{
		tmp[el->surplus_len] = '\0';
		el->surplus = NULL;
		el->surplus_len = 0;
		return (tmp);
	}
	tmp[el->surplus_len] = c;
	el->surplus_len += 1;
	el->surplus = tmp;
	return (NULL);
}

static int	gnl_seeker(t_gnl_element *el, char **line)
{
	char	*tmp_line;
	int		f;

	while (el->offset < BUFFER_SIZE)
	{
		f = (el->offset >= el->byte_read) ? 1 : 0;
		if ((tmp_line = gnl_store(el, f)))
		{
			if (f)
				el->reached = 1;
			*line = tmp_line;
			return (1);
		}
		if (tmp_line == NULL && el->reached == -1)
			return (-1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_gnl_container	container;
	t_gnl_element			*el;

	if (fd < 0 || !line || !(container_initialize(&container, 0, 0)) ||
			BUFFER_SIZE == 0)
		return (-1);
	*line = NULL;
	if (container_initialize(&container, 1, fd) == 0)
		return (check_return(NULL, &container, -1));
	el = &((container.table)[fd]);
	while (1)
	{
		if (el->offset == BUFFER_SIZE || fd == 0)
		{
			el->byte_read = read(fd, el->buffer, BUFFER_SIZE);
			el->offset = 0;
		}
		if (el->byte_read == -1)
			return (check_return(el, &container, -1));
		if (gnl_seeker(el, line))
			return (check_return(el, &container, 0));
	}
}
