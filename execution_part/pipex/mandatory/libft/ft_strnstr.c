/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:26:07 by iouardi           #+#    #+#             */
/*   Updated: 2022/03/24 00:38:08 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (str2[i] == '\0')
		return ((char *)str1);
	while (str1[i])
	{
		j = 0;
		while (str2[j] && str2[j] == str1[i + j] && i + j < len)
			j++;
		if (str2[j] == '\0')
			return ((char *)str1 + j);
		i++;
	}
	return (NULL);
}
