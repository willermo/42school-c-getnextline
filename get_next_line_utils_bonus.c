/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:31 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 03:38:40 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_fd_list	*new_fd_list(t_fd fd)
{
	t_fd_list	*new;

	new = (t_fd_list *) malloc(sizeof(t_fd_list));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->buffer = (char *) ft_calloc(BUFFER_SIZE, sizeof(char));
	new->bytes_read = 0;
	new->bytes_remaining = 0;
	new->next = NULL;
	return (new);
}

t_fd_list	*get_fd_list(t_fd_list **fd_list, t_fd fd)
{
	t_fd_list	*current;

	if (!*fd_list)
	{
		*fd_list = new_fd_list(fd);
		return (*fd_list);
	}
	current = *fd_list;
	while (current->fd != fd && current->next)
		current = current->next;
	if (current->fd == fd)
		return (current);
	current->next = new_fd_list(fd);
	return (current->next);
}
