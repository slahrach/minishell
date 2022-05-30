/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:06:17 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/19 17:33:10 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	i = 0;
	while (dst != src && n > 0)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		n--;
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	//char d[50] = "comment";
	//char s[50] = "comment";
	//char dst[50] = "comment";
	char src[50] = "comment";
	//memcpy(dst, s, 5);
	//ft_memcpy(dst, src, 5);
	//printf("%s\n",memcpy("comment", src, 4));
	//printf("%s\n",ft_memcpy("comment", src, 4));
	printf("%p\n%p\n%p", &src, src, "comment");
	//printf("%s\n%s", d, dst);
}
*/
