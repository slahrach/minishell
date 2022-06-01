/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:54:00 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/10 23:50:26 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*ptr;

	ptr = (char *)src;
	if (!dstsize)
		return (ft_strlen(src));
	while (*ptr && (ptr - src) / sizeof(char) < dstsize - 1)
	{
		*dst++ = *(char *)ptr++;
	}
	*dst = '\0';
	return (ft_strlen(src));
}
