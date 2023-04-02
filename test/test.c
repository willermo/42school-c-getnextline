/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:26:11 by doriani           #+#    #+#             */
/*   Updated: 2023/04/02 12:35:25 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "../get_next_line.h"

int	main(void)
{
	t_fd	fd;
	char	*line;

	printf("Buffer size: %d\n", BUFFER_SIZE);
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file (error %d)\n", errno);
		return (errno);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
