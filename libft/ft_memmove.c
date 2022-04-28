/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:22:07 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/16 02:16:58 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (dst > src)
	{
		i = (int) len - 1;
		while (i >= 0)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
/*
#include <stdio.h>
#include <string.h>
#include <strings.h>
int main ()
{
	char sr[10] = "abcde";
	char ds[10] = "";
	char sour[10] = "abcde";
	char des[10] = "";
	printf("%s\n",memmove(ds, sr, 3));
	printf("%s", ft_memmove(des, sour, 3));
}
*/