/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:22 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 03:38:42 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(t_fd fd)
{
	char						*line;
	static t_fd_list			*files;
	t_fd_list					*file;
	size_t						i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	file = get_fd_list(&files, fd);
	if (file->bytes_read == 0)
		file->bytes_remaining = read(fd, file->buffer, BUFFER_SIZE);
	i = 0;
	while (file->bytes_remaining)
	{
		if (i % BUFFER_SIZE == 0)
			line = expand_line_buffer(line, file->bytes_read / BUFFER_SIZE + 1);
		line[i++] = file->buffer[file->bytes_read++ % BUFFER_SIZE];
		if (file->fd == 0 && line[i - 1] == '\n')
			file->bytes_read = 0;
		else if (--file->bytes_remaining == 0)
			file->bytes_remaining = read(fd, file->buffer, BUFFER_SIZE);
		if (line[i - 1] == '\n')
			break ;
	}
	return (line);
}
