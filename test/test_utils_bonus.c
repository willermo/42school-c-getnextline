/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:47:56 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 22:48:10 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	setup_test(char *prefix, char ***filenames)
{
	// sets filenames
	*filenames = (char **) calloc(1, sizeof(char *));
	set_filenames(prefix, filenames);
}

void	set_filenames(char *prefix, char ***filenames)
{
	int		i;
	char	*number;
	char 	*filename;

	i = 0;
	number = ft_itoa(i + 1);
	filename = ft_strjoin(prefix, number, ".txt");
	free(number);
	while (access(filename, F_OK) == 0)
	{
		(*filenames)[i++] = filename;
		number = ft_itoa(i + 1);
		filename = ft_strjoin(prefix, number, ".txt");
		free(number);
		*filenames = (char **) realloc(*filenames, sizeof(char *) * (i + 1));
		(*filenames)[i] = NULL;
	}
	free(filename);
}

t_fd	open_file(char *filename, char mode)
{
	t_fd	fd;

	if (mode == 'r')
		fd = open(filename, O_RDONLY);
	else if (mode == 'w')
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = (-1);
	if (fd == -1)
	{
		yellow();
		printf("Error opening file %s (error %d)\n", filename, errno);
		reset();
		exit(errno);
	}
	return (fd);
}

void	cleanup_test(char **filenames, t_fd_list *files)
{
	// frees filenames
	free_filenames(filenames);
	// closes files
	close_files(files);
	// frees files list
	free_files_list(files);
	files = NULL;
	// frees filenames
	free(filenames);
	filenames = NULL;
}

void	close_files(t_fd_list *files)
{
	while (files)
	{
		close(files->fd);
		files = files->next;
	}
}

void	free_filenames(char **filenames)
{
	while (*filenames)
	{
		free(*filenames);
		*filenames++ = NULL;
	}
}

void	free_files_list(t_fd_list *file_list)
{
	t_fd_list	*file;

	file = file_list;
	while (file)
	{
		file_list = file_list->next;
		free(file->buffer);
		file->buffer = NULL;
		file->next = NULL;
		free(file);
		file = file_list;
	}
}

// beware: this function removes the files from the filesystem
void	remove_files(char **filenames)
{
	while (*filenames)
		remove(*filenames++);
}

// beware: this function removes the files from the filesystem
void	clean_filenames(char **filenames)
{
	remove_files(filenames);
	free_filenames(filenames);
}

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*str;

	if (!s1 || !s2 || !s3)
		return (NULL);
	str = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strlcat(str, s3, ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	return (str);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*p;

	p = dst;
	if (dstsize != 0)
	{
		while (--dstsize != 0)
		{
			*p = *src;
			if (*p == '\0')
				return (p - dst);
			p++;
			src++;
		}
		*p = '\0';
	}
	return ((p - dst) + ft_strlen(src));
}

void	ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	*ft_strrev(char *str)
{
	char	*start;
	char	*end;

	start = str;
	end = str;
	while (*(end + 1))
		end++;
	while (end > start)
		ft_swap(start++, end--);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		sign = -1;
	str = malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	while (n / 10 != 0)
	{
		str[i++] = (sign * n) % 10 + '0';
		n /= 10;
	}
	str[i++] = (sign * n) % 10 + '0';
	if (sign == -1 && i != 0)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = (char *) malloc((len + 1) * sizeof (char));
	if (! dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*p;

	p = dest;
	while (size != 0 && *p != '\0')
	{
		p++;
		size--;
	}
	if (size != 0)
	{
		while (--size != 0)
		{
			*p = *src;
			if (*p == '\0')
				return (p - dest);
			p++;
			src++;
		}
		*p = '\0';
	}
	return ((p - dest) + ft_strlen(src));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		if (*s1 == '\0')
			break ;
		s1++;
		s2++;
	}
	return (0);
}

int	compare_files(FILE *fp1, FILE *fp2)
{
	char	ch1;
	char	ch2;

	ch1 = fgetc(fp1);
	ch2 = fgetc(fp2);
	while (ch1 != EOF && ch2 != EOF)
	{
		if (ch1 != ch2)
			return(0);
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	}
	if (ch1 == EOF && ch2 == EOF)
		return (1);
	return (0);
}
