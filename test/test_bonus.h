/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:48:15 by doriani           #+#    #+#             */
/*   Updated: 2023/04/03 02:55:48 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_BONUS_H
# define TEST_BONUS_H
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include "../get_next_line_bonus.h"
# define NUMBER_OF_TESTS 10
// COLORS FUNCTIONS PROTOTYPES
void		black();
void		red();
void		green();
void		yellow();
void		blue();
void		purple();
void		cyan();
void		white();
void		reset();
// TEST FUNCTIONS PROTOTYPES
// TEST HELPER FUNCTIONS PROTOTYPES
t_fd_list	*add_file(t_fd_list *files, char *filename);
void	set_filenames(char **filenames);
void	open_files(t_fd_list *files, char **filenames);
void	close_files(t_fd_list *files);
void	free_filenames(char **filenames);
void	remove_files(char **filenames);
void	clean_filenames(char **filenames);
void	free_files_list(t_fd_list *fd_list);
char	*ft_strjoin(char const *s1, char const *s2, char const *s3);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_swap(char *a, char *b);
char	*ft_strrev(char *str);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
