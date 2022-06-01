/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 20:37:33 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/18 02:51:17 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int				i;
	int				tmp;
	unsigned int	nb;
	char			*arr;

	i = 0;
	tmp = n;
	nb = n * (n >= 0) - n * (n < 0);
	while (tmp && ++i)
		tmp /= 10;
	i += (n == 0) + (n < 0);
	arr = (char *)malloc((i + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	arr[0] = '-' * (n != 0) + '0' * (!n);
	arr[i--] = '\0';
	while (nb)
	{
		arr[i--] = nb % 10 + '0';
		nb /= 10;
	}
	return (arr);
}
