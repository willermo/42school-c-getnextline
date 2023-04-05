/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:22 by doriani           #+#    #+#             */
/*   Updated: 2023/04/06 00:49:11 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void set_line(char **line, char *buffer)
{
	int 	len;
	char	*runner;
	*line = malloc((ft_strchr(buffer, '\n') - buffer + 1) * sizeof(char));
	if (!*line)
		return ;
	len = ft_strlen(buffer);
	runner = buffer;
	while (*buffer != '\n' && *buffer != '\0')
		*line++ = *buffer++;
	*line = '\0';
	while (*buffer != '\0')
	{
		*runner++ = *buffer++;
		len--;
	}
	while(len--)
		*runner++ = '\0';
}

char	*get_next_line(t_fd fd)
{
	char		*line;
	char		*read_buffer;
	static char	*line_buffer;
	int			bytes_read;
	size_t		dim;

	if (fd < 0 || fd >= 4096 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return(NULL);
	read_buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!read_buffer)
		return (NULL);
	dim = 0;
	bytes_read = 0;
	while (!ft_strchr(line_buffer, '\n') && bytes_read >= 0)
	{
		line_buffer = expand_line_buffer(line_buffer, dim++);
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		ft_memset(read_buffer + bytes_read, 0, BUFFER_SIZE - bytes_read);
		ft_strlcat(line_buffer, read_buffer, BUFFER_SIZE * dim);
		ft_memset(read_buffer, 0, BUFFER_SIZE);
	}
	set_line(&line, line_buffer);
	free(read_buffer);
	return (line);
}
