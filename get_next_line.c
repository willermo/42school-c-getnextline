/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:22 by doriani           #+#    #+#             */
/*   Updated: 2023/04/06 16:17:35 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*expand_line_buffer(char *line)
{
	char	*buf;
	char 	*buf_runner;
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

static int add_chunk(char **line, char *storage, t_fd fd)
{
	int		i;
	char	*line_runner;

	line_runner = *line;
	while (*line_runner)
		line_runner++;
	i = 0;
	printf("START\n");
	while(i < BUFFER_SIZE && storage[i] != '\0')
	{
		line_runner[i] = storage[i];
		i++;
		if (line_runner[i - 1] == '\n')
		{
			ft_memmove(storage, storage + i, BUFFER_SIZE - i);
			ft_memset(storage + i, '\0', BUFFER_SIZE - i);
			printf("Line in: %s\n", *line);
			return (0);
		}
	}
	printf("Line: %s\n", *line);
	sleep(1);
	if (i == BUFFER_SIZE)
	{
		*line = expand_line_buffer(*line);
		return (read(fd, storage, BUFFER_SIZE));
	}
	ft_memmove(storage, storage + i, BUFFER_SIZE - i);
	ft_memset(storage + i, '\0', BUFFER_SIZE - i);
	return (1);
}

char	*get_next_line(t_fd fd)
{
	char		*line;
	static char	storage[BUFFER_SIZE];

	if (fd < 0 || fd >= 4096 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return(NULL);
	line = expand_line_buffer(NULL);
	while (line && add_chunk(&line, storage, fd) > 0)
		;
	return (line);
}
