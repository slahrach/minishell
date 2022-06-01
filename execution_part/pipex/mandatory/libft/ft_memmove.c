/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:33:57 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/18 01:35:49 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp;
	unsigned char	*s;

	temp = dst;
	s = (unsigned char *)src;
	if (!temp && !s)
		return (NULL);
	if (!ft_memcmp(temp, s, len))
		return (dst);
	if (temp > s && temp < s + len && len)
	{
		temp += len;
		s += len;
		while (len--)
			*--temp = *--s;
	}
	else
		while (len--)
			*temp++ = *(unsigned char *)src++;
	return (dst);
}
