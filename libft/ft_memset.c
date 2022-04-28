/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:56:37 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/26 22:58:50 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, size_t count)
{
	int	i;

	i = 0;
	while (count > 0)
	{
		*(unsigned char *)(ptr + i) = (unsigned char)x;
		i++;
		count--;
	}
	return (ptr);
}
/*
#include <string.h>
#include <stdio.h>
int main()
{
	char	str[50] = "para";
	char	s[50] = "para";
	printf("%s\n",memset(str, 's', 9));
	printf("%s\n",ft_memset(s, 's', 9));
	printf("%s\n%s",str,s);
}*/
