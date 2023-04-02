/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:31 by doriani           #+#    #+#             */
/*   Updated: 2023/04/02 12:08:27 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*expand_line_buffer(char *line, size_t dim)
{
	char	*new_line;

	new_line = (char *) ft_calloc(sizeof(char), dim * BUFFER_SIZE + 1);
	if (!line)
		return (new_line);
	ft_memcpy(new_line, line, (dim - 1) * BUFFER_SIZE);
	free(line);
	return (new_line);
}

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
