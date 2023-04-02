/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:26:11 by doriani           #+#    #+#             */
/*   Updated: 2023/04/02 17:53:49 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(void)
{
	char	*files[11];
	char	file_out[20];
	t_fd	out;
	t_fd_list	*fd_list;
	t_fd_list	*fd_runner;
	char	*line;
	int		i;
	int		result;

	i = 0;
	while (i < NUMBER_OF_TESTS)
	{
		files[i] = ft_strjoin("test", ft_itoa(i + 1), ".txt");
		i++;
	}
	files[i] = NULL;
	fd_list = malloc(sizeof(t_fd_list));
	fd_list->fd = -1;
	fd_list->next = NULL;

	printf("Testing get_next_line\n");
	printf("Buffer size: %d\n", BUFFER_SIZE);
	fd_runner = fd_list;
	i = 0;
	while (i < NUMBER_OF_TESTS)
	{
		fd_runner->fd = open(files[i], O_RDONLY);
		if (fd_runner->fd == -1)
		{
			printf("Error opening file %s (error %d)\n", *files, errno);
			free_files(files);
			return (errno);
		}
		i++;
		fd_runner->next = malloc(sizeof(t_fd_list));
		fd_runner = fd_runner->next;
		fd_runner->fd = -1;
		fd_runner->next = NULL;
	}
	fd_runner = fd_list;
	i = 0;
	while (fd_runner->fd != -1)
	{
		printf("Test %d - fd %d\n", i + 1, fd_runner->fd);
		strcpy(file_out, files[i]);
		strcat(file_out, ".out");
		out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		line = get_next_line(fd_runner->fd);
		while (line)
		{
			printf("%s", line);
			write(out, line, strlen(line));
			free(line);
			line = get_next_line(fd_runner->fd);
		}
		close(out);
		result = NULL;
		if (execl("diff", "diff", files[i], file_out, NULL))
			printf("Test %d passed (file: %s)\n", i + 1, files[i]);
		else
			printf("Test %d failed (file: %s)\n", i + 1, files[i]);
		i++;
		fd_runner = fd_runner->next;
	}
	free_files(files);
	free_files_list(fd_list);
	return (0);
}
