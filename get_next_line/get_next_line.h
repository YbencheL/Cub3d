/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:45:46 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/06/27 21:41:18 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_substr_get(const char *s, unsigned int start, size_t len);
size_t	ft_strlcpy_get(char *dst, const char *src, size_t dstsize);
char	*ft_strchr_get(const char *s, int c);
char	*ft_strjoin_get(char *s1, const char *s2);
char	*ft_strdup_get(const char *s1);
size_t	ft_strlen_get(const char *s);

#endif
