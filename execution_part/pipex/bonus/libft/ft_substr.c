/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:31:56 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/16 15:42:48 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;
	size_t			temp;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		temp = ft_strlen(s);
	else
		temp = len;
	if (start >= ft_strlen(s))
	{
		ptr = malloc(sizeof(char) * 1);
		ptr[0] = '\0';
		return (ptr);
	}
	ptr = malloc((temp + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < temp)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}
