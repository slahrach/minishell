/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:05:21 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/28 01:47:28 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy( char *dst, const char *src, size_t sizedst)
{
	size_t	l;
	size_t	i;

	l = ft_strlen(src);
	i = 0;
	if (sizedst == 0)
		return (l);
	while (src[i] && i < (sizedst - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}
/*
#include <string.h>
#include <stdio.h>
int main() 
{
  char *src = NULL;
  char dst[] = "JFJG";
  char *src2 = NULL;
  char dst2[] = "HFHF";
  printf("%lu\n", ft_strlcpy(dst2, src2, 5));
  printf("%lu\n",strlcpy(dst, src, 5));
  
  return 0;
}*/
