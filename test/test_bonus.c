/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:26:11 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 17:24:49 by doriani          ###   ########.fr       */
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
	while (files)
	{
		//sets file_out to the same string as file_in, but with ".out" appended
		out_filename = (char *) malloc(ft_strlen(*filenames) + 4);
		ft_strlcpy(out_filename, *filenames, ft_strlen(*filenames) - 3);
		ft_strlcat(out_filename, ".out", ft_strlen(*filenames) + 4);
		out = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out == -1)
		{
			yellow();
			printf("Error opening file_out: %s (error %d)\n", out_filename, errno);
			reset();
			return (errno);
		}
		cyan();
		printf("Testing file %s\n", *filenames);
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
		if (execl("diff", "diff", *filenames, out_filename, NULL))
		{
			green();
			printf("Test for file: %s passed\n\n", *filenames);
			reset();
		}
		else
		{
			red();
			printf("Test for file: %s failed\n", *filenames);
			reset();
		}
		remove(out_filename);
		free(out_filename);
		files = files->next;
		filenames++;
	}
	return (0);
}

int	run_static_test2(t_fd_list *files, char **filenames)
{
	t_fd		out;
	t_fd		out_compare;
	char		*out_filename;
	char		*out_compare_filename;
	char		*line;
	int			files_number;
	t_fd_list	*runner;
	int			i;

	files_number = 0;
	runner = files;
	// counts file number
	while (runner)
	{
		files_number++;
		runner = runner->next;
	}
	// Creates output file
	out_filename = "TestB.out";
	out = open(out_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		yellow();
		printf("Error opening file_out: %s (error %d)\n", out_filename, errno);
		reset();
		return (errno);
	}
	// Opens comparison file
	out_compare_filename = "TestB.compare";
	out_compare = open(out_compare_filename, O_RDONLY);
	if (out_compare == -1)
	{
		yellow();
		printf("Error opening comparison file: %s (error %d)\n", out_compare_filename, errno);
		reset();
		return (errno);
	}
	// Prints file names
	cyan();
	printf("Testing alternated file reading:\n");
	while(*filenames)
	{
		printf("%s\n", *filenames);
		filenames++;
	}
	reset();
	// Reads files alternately
	runner = files;
	i = 0;
	while (i < files_number)
	{
		line = get_next_line(runner->fd);
		if (line)
		{
			printf("%s", line);
			write(out, line, ft_strlen(line));
			free(line);
		}
		else if(!line && i == files_number - 1)
			break;
		if (i == files_number - 1)
		{
			runner = files;
			i = 0;
		}
		else
		{
			runner = runner->next;
			i++;
		}
	}
	// Closes files and compares output
	close(out);
	close(out_compare);
	if (execl("diff", "diff", out_filename, out_compare_filename, NULL))
	{
		green();
		printf("Alternate reading passed\n\n");
		reset();
	}
	else
	{
		red();
		printf("Alternate reading failed\n");
		reset();
	}
	// Removes output file
	remove(out_filename);
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
		filenames = (char **) calloc(1, sizeof(char *));
		set_filenames("testA", &filenames);
		//opens files
		files = NULL;
		open_files(&files, filenames);
		// runs static test 1
		result = run_static_test1(files, filenames);
		//closes files
		close_files(files);
		// cleanup
		static_cleanup(&files, filenames);
		free(filenames);
		filenames = NULL;

		//sets filenames
		filenames = (char **) calloc(1, sizeof(char *));
		set_filenames("TestB", &filenames);
		//opens files
		files = NULL;
		open_files(&files, filenames);
		// runs static test 2
		result = run_static_test2(files, filenames);
		//closes files
		close_files(files);
		// cleanups
		static_cleanup(&files, filenames);
		free(filenames);
		filenames = NULL;
	}
	else
	{
		print_usage();
		return (1);
	}
	return (result);
}
