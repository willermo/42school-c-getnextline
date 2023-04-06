/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:31 by doriani           #+#    #+#             */
/*   Updated: 2023/04/06 13:37:50 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int		bytes;

	bytes = count * size;
	ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	while (bytes--)
		((char *)ptr)[bytes] = 0;
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d == s)
		return (dest);
	if (s < d && s + n > d)
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*runner;

	runner = (unsigned char *) s;
	i = 0;
	while (i < n)
		runner[i++] = c;
	return (s);
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

char	*ft_strchr(const char *s, int c)
{
	char	*runner;

	runner = (char *) s;
	while (*runner)
	{
		if (*runner == c)
			return (runner);
		runner++;
	}
	if (*runner == c)
		return (runner);
	return (NULL);
}
