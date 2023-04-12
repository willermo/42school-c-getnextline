/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:22 by doriani           #+#    #+#             */
/*   Updated: 2023/04/12 22:22:30 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*expand_line_buffer(char *line)
{
	char	*buf;
	char	*buf_runner;
	char	*line_runner;

	if (!line)
		return ((char *) ft_calloc(sizeof(char), BUFFER_SIZE + 1));
	buf = (char *) ft_calloc(sizeof(char), ft_strlen(line) + BUFFER_SIZE + 1);
	line_runner = line;
	buf_runner = buf;
	while (*line_runner)
		*buf_runner++ = *line_runner++;
	free(line);
	return (buf);
}

static int	feed_buffer(char *buffer, int index, t_fd fd)
{
	ft_memmove(buffer, buffer + index, BUFFER_SIZE - index);
	ft_memset(buffer + BUFFER_SIZE - index, '\0', index);
	if (index == BUFFER_SIZE || index == 0)
		return (read(fd, buffer, BUFFER_SIZE));
	return (0);
}

static int	add_chunk(char *line, char *storage, t_fd fd)
{
	int		i;

	while (*line)
		line++;
	i = 0;
	while (i < BUFFER_SIZE && storage[i])
	{
		line[i] = storage[i];
		if (line[i++] == '\n')
			break ;
	}
	return (feed_buffer(storage, i, fd));
}

char	*get_next_line(t_fd fd)
{
	char		*line;
	static char	storage[BUFFER_SIZE];

	if (fd < 0 || fd >= 4096 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	line = expand_line_buffer(NULL);
	while (line && add_chunk(line, storage, fd) > 0)
		line = expand_line_buffer(line);
	if (line && !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
