/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:15:15 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/14 17:43:32 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	retur(int sign, unsigned long long n)
{
	if (n >= 9223372036854775808U && sign == 1)
		return (0);
	if (n > 9223372036854775808U && sign == -1)
		return (0);
	return (n * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	nbr;

	sign = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' )
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (*str)
		return (0);
	return (retur(sign, nbr));
}
/*
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
	char str[50] = "9223372036854775808";
	printf("%d\n",atoi(str));
	printf("%d",ft_atoi(str));
}*/
