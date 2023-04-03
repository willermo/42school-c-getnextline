/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:26:11 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 11:18:14 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

// COLORS
void	black()		{ printf("\033[1;30m"); }
void	red()		{ printf("\033[1;31m"); }
void	green()		{ printf("\033[1;32m"); }
void	yellow() 	{ printf("\033[1;33m"); }
void	blue()		{ printf("\033[1;34m"); }
void	purple()	{ printf("\033[1;35m"); }
void	cyan()		{ printf("\033[1;36m"); }
void	white()		{ printf("\033[1;37m"); }
void	reset () 	{ printf("\033[0m"); }

void print_usage(void)
{
	printf("Usage: <executable_file> [ static | interactive ]\n");
}

int	run_static_test1(t_fd_list *files, char **filenames)
{
	t_fd		out;
	char		*out_filename;
	char		*line;
	int			i;

	i = 0;
	while (i < NUMBER_OF_TESTS)
	{
		//sets file_out to the same string as file_in, but with ".out" appended
		out_filename = malloc(ft_strlen(filenames[i]) + 4);
		ft_strlcpy(out_filename, filenames[i], ft_strlen(filenames[i]) - 3);
		ft_strlcat(out_filename, ".out", ft_strlen(filenames[i]) + 4);
		out = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out == -1)
		{
			yellow();
			printf("Error opening file_out: %s (error %d)\n", out_filename, errno);
			reset();
			return (errno);
		}
		cyan();
		printf("Testing file %s\n", filenames[i]);
		reset();
		line = get_next_line(files->fd);
		while (line)
		{
			//printf("%s", line);
			write(out, line, ft_strlen(line));
			free(line);
			line = get_next_line(files->fd);
		}
		close(out);
		if (execl("diff", "diff", filenames[i], out_filename, NULL))
		{
			green();
			printf("Test for file: %s passed\n\n", filenames[i]);
			reset();
		}
		else
		{
			red();
			printf("Test for file: %s failed\n", filenames[i]);
			reset();
		}
		remove(out_filename);
		free(out_filename);
		files = files->next;
		i++;
	}
	return (0);
}

void	run_interactive_test(void)
{
	t_fd	in;
	t_fd	out;
	char	*line;

	in = 0;
	out = 1;
	cyan();
	printf("Interactive testing\n");
	reset();
	printf("Enter text to test get_next_line (^D to end)\n");
	line = get_next_line(in);
	while (line)
	{
		write(out, line, ft_strlen(line));
		free(line);
		line = get_next_line(in);
	}
}

int	main(int argc, char **argv)
{
	char		**filenames;
	t_fd_list	*files;
	int			result;

	if(argc != 2)
	{
		print_usage();
		return (1);
	}

	result = 0;
	blue();
	printf("Testing get_next_line\n");
	printf("Buffer size: %d\n", BUFFER_SIZE);
	reset();
	printf("----------------------------\n");
	if (ft_strncmp(argv[1], "interactive", 11) == 0)
		run_interactive_test();
	else if (ft_strncmp(argv[1], "static", 6) == 0)
	{
		//sets filenames
		filenames = malloc(sizeof(char *) * NUMBER_OF_TESTS);
		set_filenames(filenames);
		//opens files
		files = NULL;
		open_files(&files, filenames);
		// runs static test 1
		result = run_static_test1(files, filenames);
		//closes files
		close_files(files);
		// cleanup
		static_cleanup(&files, &filenames);
	}
	else
	{
		print_usage();
		return (1);
	}
	return (result);
}
