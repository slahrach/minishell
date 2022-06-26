/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:58:33 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 00:41:08 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	if (start >= l)
		return (ft_strdup(""));
	if (start + len > l)
		len = l - start;
	ptr = (char *) malloc ((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (len > 0 && *(s + start) != '\0')
	{
		ptr[i] = *(s + start);
		i++;
		start++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>
int main()
{
	char s[16] = "what would i do";
	printf("%s\n",ft_substr(s, 9, 180));
	system("leaks a.out");
}*/
