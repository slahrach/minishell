/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:04:10 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/18 02:49:48 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	exist(const char c, const char *s2)
{
	int		j;

	j = 0;
	while (s2[j])
	{
		if (c == s2[j])
			return (1);
		j++;
	}
	return (0);
}

static	int	calculate_first(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (exist(s1[i], s2))
		i++;
	return (i);
}

static	int	calculate_last(const char *s1, const char *s2)
{
	int		i;

	i = ft_strlen(s1) - 1;
	while (exist(s1[i], s2) && i)
		i--;
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		first;
	int		last;
	char	*arr;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	first = calculate_first(s1, set);
	last = calculate_last(s1, set);
	if (last - first + 2 < 0)
	{
		arr = ft_calloc(1, sizeof(char));
		if (!arr)
			return (NULL);
		return (arr);
	}
	arr = ft_calloc(last - first + 2, sizeof(char));
	if (!arr)
		return (NULL);
	i = first;
	j = 0;
	while (i <= last)
		arr[j++] = s1[i++];
	return (arr);
}
