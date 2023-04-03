/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:47:56 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 01:11:10 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	free_files(char **files)
{
	int i;

	i = 0;
	while (i < NUMBER_OF_TESTS)
	{
		free(files[i]);
		i++;
	}
}

void	remove_files(char **files)
{
	int i;

	i = 0;
	while (i < NUMBER_OF_TESTS)
	{
		remove(files[i]);
		i++;
	}
}

void	clean_files(char **files)
{
	remove_files(files);
	free_files(files);
}

void	free_files_list(t_fd_list *fd_list)
{
	t_fd_list	*fd_runner;

	fd_runner = fd_list;
	while (fd_runner)
	{
		fd_list = fd_list->next;
		free(fd_runner);
		fd_runner = fd_list;
	}
}

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*str;

	if (!s1 || !s2 || !s3)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
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

