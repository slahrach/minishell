/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:22:03 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/16 01:42:46 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		*(char *)(s + i) = '\0';
		n--;
		i++;
	}
}
/*
#include <strings.h>
#include <stdio.h>
int main()
{
	char str1[] = "sara khayba ismail zwin";
	char str2[] = "sara khayba ismail zwin";
	bzero(str1 + 2, 5);
	ft_bzero(str2 + 2, 5);
	printf("%s\n", str1);
	printf("%s", str2);
}
*/
