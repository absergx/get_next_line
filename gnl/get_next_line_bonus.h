/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:06:12 by memilio           #+#    #+#             */
/*   Updated: 2020/07/10 15:36:58 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_gnl_element
{
	int				init;
	int				reached;
	int				fd;
	int				byte_read;
	int				offset;
	char			*surplus;
	int				surplus_len;
	char			buffer[BUFFER_SIZE];
}					t_gnl_element;

typedef struct		s_gnl_container
{
	int				init;
	int				size;
	int				opened;
	t_gnl_element	*table;
}					t_gnl_container;

int					get_next_line(int fd, char **line);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					gigalloc(t_gnl_container *container, int f);
int					container_initialize(t_gnl_container *container, int f,
					int i);
int					check_return(t_gnl_element *el, t_gnl_container *container,
					int ret);

#endif
