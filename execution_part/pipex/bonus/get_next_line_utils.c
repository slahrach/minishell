/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   get_next_line_utils.c	  :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: iouardi <iouardi@student.42.fr>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2021/11/27 23:42:26 by iouardi	   #+#	#+#	 */
/*   Updated: 2021/11/27 23:43:46 by iouardi	  ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	j;

	j = -1;
	i = ft_strlen(str);
	while (++j < i)
	{
		if (str[j] == (char)c)
			return ((char *)(str + j + 1));
	}
	if (str[j] == c)
		return ((char *)(str + j));
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	dsst_length;
	size_t	i;

	if (!dst && !size)
		return (ft_strlen(src));
	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	dsst_length = src_length;
	i = 0;
	if (dst_length < size)
		dsst_length += dst_length;
	else
		dsst_length += size;
	while (src[i] && dst_length + 1 < size)
	{
		dst[dst_length++] = src[i++];
	}
	dst[dst_length] = '\0';
	return (dsst_length);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	arr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	arr[0] = '\0';
	ft_strlcat(arr, s1, ft_strlen(s1) + 1);
	ft_strlcat(arr, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (arr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
	i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;

	if (!dest && !src)
		return (0);
	temp = dest;
	while (n--)
		*temp++ = *(unsigned char *)src++;
	return (dest);
}
