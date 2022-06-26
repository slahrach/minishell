/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:12:05 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/20 22:37:52 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n, int *c)
{
	long	nbr;
	int		r;

	nbr = n;
	*c = 1;
	r = 1;
	if (nbr < 0)
	{
		r++;
		nbr *= -1;
	}
	while (nbr > 9)
	{
		r++;
		nbr /= 10;
		*c *= 10;
	}
	return (r);
}

char	*ft_itoa(int nbr)
{
	long	n;
	char	*str;
	char	*ptr;
	int		r;
	int		a;

	n = nbr;
	r = count (n, &a);
	str = (char *) malloc ((r + 1) * sizeof (char));
	if (!str)
		return (NULL);
	ptr = str;
	if (n < 0)
	{
		*str++ = '-';
		n *= (-1);
	}
	while (a >= 1)
	{
		*str++ = (n / a) + '0';
		n %= a;
		a /= 10;
	}
	*str = '\0';
	return (ptr);
}
/*
#include <stdio.h>
int main ()
{
	printf("%s\n",ft_itoa(-1234));
}*/
