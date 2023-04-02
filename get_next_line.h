/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:50:39 by doriani           #+#    #+#             */
/*   Updated: 2023/04/02 12:32:44 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef int	t_fd;
typedef struct fd_list
{
	t_fd			fd;
	struct fd_list	*next;
}	t_fd_list;
/* BASE FUNCTION PROTOTYPE */
char	*get_next_line(int fd);
/* HELPER FUNCTIONS PROTOTYPES */
char	*expand_line_buffer(char *line, size_t dim);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
#endif
