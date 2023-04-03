/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:39 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 23:50:47 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
#include <unistd.h>
#include <stdlib.h>

typedef int	t_fd;
typedef struct fd_list
{
	t_fd			fd;
	char			*buffer;
	int				bytes_read;
	size_t			bytes_remaining;
	struct fd_list	*next;
}	t_fd_list;
char		*get_next_line(int fd);
char		*expand_line_buffer(char *line, size_t dim);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
t_fd_list	*new_file(t_fd fd);
t_fd_list	*get_file(t_fd_list **fd_list, t_fd fd);
#endif
