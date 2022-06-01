/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:48:04 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/08 19:31:50 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	j;

	j = -1;
	i = ft_strlen(str);
	while (++j < i)
	{
		if (str[j] == (char)c)
			return ((char *)(str + j));
	}
	if (str[j] == c)
		return ((char *)(str + j));
	return (NULL);
}
