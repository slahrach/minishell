/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:54:05 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/21 23:02:32 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_strndup(const char *s1, int l)
{
	char	*ptr;

	ptr = (char *) malloc ((l + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy (ptr, s1, l + 1);
	return (ptr);
}

static int	count(const char *str, char c)
{
	size_t	i;
	int		r;

	i = 0;
	r = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c && i != 0)
		{
			if (str[i - 1] != c)
				r++;
		}
		if (i == ft_strlen(str) - 1)
		{
			if (str[i] == c)
				r--;
		}
		i++;
	}
	return (r);
}

static void	free_multi(char	**ptr, int j)
{
	while (j > 0)
	{
		free(ptr[j - 1]);
		j--;
	}
	free(ptr);
}

static void	fill(char	**ptr, int r, char const *s, char c)
{
	int	j;
	int	st;
	int	i;

	j = 0;
	i = 0;
	while (j < r)
	{
		while (s[i] == c)
			i++;
		st = i;
		while (s[i] != c && s[i])
			i++;
		ptr[j] = ft_strndup(s + st, i - st);
		if (!ptr[j])
		{
			free_multi(ptr, j);
			return ;
		}
		j++;
	}
	ptr[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		r;
	char	**ptr;

	if (!s)
		return (NULL);
	r = count(s, c);
	ptr = (char **)malloc((r + 1) * sizeof (char *));
	if (!ptr)
		return (NULL);
	fill (ptr, r, s, c);
	return (ptr);
}
/*
#include <stdio.h>
int main()
{
	int	i;
	i = 0;
	char **ptr;
	char s[] = "54\t5\t54541";
	ptr = ft_split(s, '\t');
	while(ptr[i] != NULL)
	{
		printf("%s\n",ptr[i]);
		i++;
	}
}
*/