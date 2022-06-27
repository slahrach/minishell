/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:31:58 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/07 01:05:59 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	char	*ptr;
	size_t	end;
	size_t	i;

	if (!s1)
		return (NULL);
	end = 0;
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_strchr(set, s1[ft_strlen(s1) - end - 1]))
		end++;
	ptr = ft_substr(s1, i, ft_strlen(s1) - i - end);
	return (ptr);
}
/*
#include <stdio.h>
int main()
{
	printf("'%s'", ft_strtrim("    ", " "));
}*/
