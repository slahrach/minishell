/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:46:16 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 05:05:39 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *origin, const char *find, size_t len)
{
	size_t	l;
	size_t	i;
	size_t	a;

	i = 0;
	l = ft_strlen(find);
	a = len;
	if ((origin[0] == '\0' && find[0] == '\0')
		|| (len == 0 && find[0] == '\0'))
		return ((char *)origin);
	while (origin[i] != '\0' && len > 0 && i + l <= a)
	{
		if (ft_memcmp (origin + i, find, l) == 0)
			return ((char *)origin + i);
		len--;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char s1[] = "yy";
	char s2[] = "";
	//size_t max = strlen(s2);
	printf("%s\n",strnstr(s1, s2, 0));
	printf("%s",ft_strnstr(s1, s2, 0));
}*/
