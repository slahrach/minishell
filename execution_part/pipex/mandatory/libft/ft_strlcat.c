/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:22:38 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/18 04:16:01 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
