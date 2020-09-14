/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memilio <memilio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:56:37 by memilio           #+#    #+#             */
/*   Updated: 2020/07/11 21:09:44 by memilio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*ft_strdup(char *str, int f);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char *s1, char const *s2);
int		get_next_line(int fd, char **line);

#endif
