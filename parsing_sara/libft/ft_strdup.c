/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:49:29 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 06:53:45 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	l;

	if (!s1)
		return (NULL);
	l = ft_strlen(s1);
	ptr = (char *) malloc ((l + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy (ptr, s1, l + 1);
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	printf("%s\n",ft_strdup("memories"));
	printf("%s",strdup("memories"));
}*/
