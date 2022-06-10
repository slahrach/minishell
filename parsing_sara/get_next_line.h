/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:43:12 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/10 23:12:00 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 100

char	*get_next_line(int fd);
size_t	ft_strlen_gl(const char *s);
char	*ft_strdup_gl(const char *s1);
int		check_newLine(char *str);
char	*ft_strljoin_gl(char const *s1, char const *s2, size_t len);
char	*ft_strjoin_gl(char *s1, char *s2);
char	*ft_strchr_gl(const char *str, int c);
void	*ft_memcpy_gl(void *dest, const void *src, size_t n);
size_t	ft_strlcat_gl(char *dst, const char *src, size_t size);

#endif