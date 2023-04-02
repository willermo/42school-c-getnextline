/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:22 by doriani           #+#    #+#             */
/*   Updated: 2023/04/02 19:27:50 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(t_fd fd)
{
	char						*line;
	static char					buffer[BUFFER_SIZE];
	static int					bytes_read;
	static size_t				bytes_remaining;
	size_t						i;

	line = NULL;
	if (bytes_read == 0)
		bytes_remaining = read(fd, buffer, BUFFER_SIZE);
	i = 0;
	while (bytes_remaining)
	{
		if (i % BUFFER_SIZE == 0)
			line = expand_line_buffer(line, bytes_read / BUFFER_SIZE + 1);
		line[i++] = buffer[bytes_read++ % BUFFER_SIZE];
		if (--bytes_remaining == 0)
			bytes_remaining = read(fd, buffer, BUFFER_SIZE);
		if (line[i - 1] == '\n')
			break ;
	}
	return (line);
}
