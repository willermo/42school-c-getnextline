/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 12:26:11 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 00:35:07 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
	printf("Usage: ./test [ <file name> | interactive ]\n");
}

int	run_static_test(char *file_in, char *file_out)
{
	t_fd	in;
	t_fd	out;
	char	*line;

	cyan();
	printf("Testing file %s\n", file_in);
	reset();
	in = open(file_in, O_RDONLY);
	if (in == -1)
	{
		yellow();
		printf("Error opening file_in: %s (error %d)\n", file_in, errno);
		reset();
		return (errno);
	}
	out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out == -1)
	{
		yellow();
		printf("Error opening file_out: %s (error %d)\n", file_out, errno);
		reset();
		return (errno);
	}
	line = get_next_line(in);
	while (line)
	{
		printf("%s", line);
		write(out, line,ft_strlen(line));
		free(line);
		line = get_next_line(in);
	}
	close(out);
	if (execl("diff", "diff", file_in, file_out, NULL))
	{
		green();
		printf("\nTest for file: %s passed\n", file_in);
		reset();
	}
	else
	{
		red();
		printf("\nTest for file: %s failed\n", file_in);
		reset();
	}
	remove(file_out);
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
	char	*file_in;
	char	*file_out;
	int		result;

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
	else
	{
		//sets file_in to the first argument
		file_in = ft_strdup(argv[1]);
		//sets file_out to the same string as file_in, but with ".out" appended
		file_out = malloc(ft_strlen(file_in) + 4);
		ft_strlcpy(file_out, file_in, ft_strlen(file_in) - 3);
		ft_strlcat(file_out, ".out", ft_strlen(file_in) + 4);
		// runs the test
		result = run_static_test(file_in, file_out);
		free(file_in);
		free(file_out);
	}
	return (result);
}
