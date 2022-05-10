/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:36:22 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/09 23:24:02 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	l;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	while (i <= l)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

int	ft_strchr1(const char *s, int c)
{
	size_t	l;
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	l = ft_strlen(s);
	while (i <= l)
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}
