/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:53:15 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/08 19:54:56 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_newline(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (*s == '\n')
				return (1);
			s++;
		}
	}
	return (0);
}

static char	*extra(char *line, char *buffer)
{
	if (!line)
		line = ft_strdup("\n");
	return (free(buffer), line);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	int		readed;

	line = NULL;
	readed = 1;
	buffer = malloc(sizeof(char) * (1 + 1));
	while (readed && !ft_newline(line))
	{
		readed = read(fd, buffer, 1);
		if (readed == -1)
			return (free(buffer), NULL);
		if (!readed)
		{
			line = ft_strdup("\0");
			return (free(buffer), line);
		}
		if (buffer[0] == '\n')
			return (extra(line, buffer));
		buffer[readed] = 0;
		line = ft_strjoin(line, buffer);
	}
	return (free(buffer), line);
}
