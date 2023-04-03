/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:26:11 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 22:50:32 by doriani          ###   ########.fr       */
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

int	run_static_test1(char **filenames)
{
	t_fd		in;
	t_fd		out;
	char		*out_filename;
	char		*line;
	FILE		*fp1;
	FILE		*fp2;

	while (*filenames)
	{
		//sets file_out to the same string as file_in, but with ".out" appended
		out_filename = (char *) malloc(ft_strlen(*filenames) + 4);
		ft_strlcpy(out_filename, *filenames, ft_strlen(*filenames) - 3);
		ft_strlcat(out_filename, ".out", ft_strlen(*filenames) + 4);
		out = open_file(out_filename, 'w');
		cyan();
		printf("Testing file %s\n", *filenames);
		reset();
		in = open_file(*filenames, 'r');
		printf("in: %s, out: %s, fd_in: %d, fd_out: %d\n", *filenames, out_filename, in, out);
		line = get_next_line(in);
		while (line)
		{
			//printf("%s", line);
			write(out, line, ft_strlen(line));
			free(line);
			line = get_next_line(in);
		}
		close(in);
		close(out);
		fp1 = fopen(out_filename, "r");
		fp2 = fopen(*filenames, "r");
		if (compare_files(fp1, fp2))
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
		fclose(fp1);
		fclose(fp2);
		remove(out_filename);
		free(out_filename);
		filenames++;
	}
	return (0);
}

int	run_static_test2(char **filenames)
{
	t_fd		*fd_list;
	t_fd		out;
	t_fd		out_compare;
	char		*out_filename;
	char		*out_compare_filename;
	char		*line;
	char		**filenames_runner;
	int			i;
	int			files_number;
	int			consecutive_null_counts;
	FILE		*fp1;
	FILE		*fp2;

	// counts file number
	files_number = 0;
	filenames_runner = filenames;
	while (*filenames_runner++)
		files_number++;

	// Sets the array of file descriptors
	fd_list = (t_fd *) calloc(files_number, sizeof(t_fd));
	i = 0;
	while (i < files_number)
	{
		fd_list[i] = open_file(filenames[i], 'r');
		printf("File: %s, fd: %d\n", filenames[i], fd_list[i]);
		i++;
	}

	// Creates output file
	out_filename = "testB.out";
	out = open_file(out_filename, 'w');

	// Opens comparison file
	out_compare_filename = "testB.compare";
	out_compare = open_file(out_compare_filename, 'r');

	// Prints file names
	cyan();
	printf("Testing alternated file reading:\n");
	filenames_runner = filenames;
	while(*filenames_runner)
		printf("%s\n", *filenames_runner++);
	reset();

	// Reads files alternately
	i = 0;
	consecutive_null_counts = 0;
	while (consecutive_null_counts < files_number)
	{
		line = get_next_line(fd_list[i % files_number]);
		if (line)
		{
			//printf("%s", line);
			write(out, line, ft_strlen(line));
			free(line);
			consecutive_null_counts = 0;
		}
		else
			consecutive_null_counts++;
		i++;
	}

	// Closes files and compares output
	close(out);
	close(out_compare);
	fp1 = fopen(out_filename, "r");
	fp2 = fopen(out_compare_filename, "r");
	if (compare_files(fp1, fp2))
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
	fclose(fp1);
	fclose(fp2);
	// Removes output file
	remove(out_filename);

	// Frees memory
	free(fd_list);
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
		files = NULL;
		// runs static test 1
		setup_test("testA", &filenames);
		result = run_static_test1(filenames);
		cleanup_test(filenames, files);
		files = NULL;
		// runs static test 2
		setup_test("testB", &filenames);
		result = run_static_test2(filenames);
		cleanup_test(filenames, files);
	}
	else
		print_usage();
	return (result);
}
