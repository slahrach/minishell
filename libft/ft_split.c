/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:54:05 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/03 22:42:25 by iouardi          ###   ########.fr       */
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

static void	fill_1(char	**ptr, int r, char const *s, char c, int i)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		ptr[j] = ft_strdup(s);
		j++;
	}
	else
		while (j < 2)
		{
			if (j == 0)
				ptr[j] = ft_strndup(s, r);
			else
				ptr[j] = ft_strdup(ft_strchr(s, c) + 1);
			if (!ptr[j])
			{
				free_multi(ptr, j);
				return ;
			}
			j++;
		}
	ptr[j] = NULL;
}

char	**ft_split1(char const *s, char c)
{
	int		r;
	char	**ptr;
	int		i;

	if (!s)
		return (NULL);
	r = 0;
	i = 1;
	while (s[r] != c && s[r])
		r++;
	if (r == (int)ft_strlen(s))
		i = 0;
	ptr = (char **)malloc((3) * sizeof (char *));
	if (!ptr)
		return (NULL);
	fill_1 (ptr, r, s, c, i);
	return (ptr);
}

// #include <stdio.h>
// int main()
// {
// 	char *str  = "hjgjhkjlk";
// 	int i = 0;
// 	char **s = ft_split1(str, '=');
// 	while (s[i])
// 	{
// 		printf("%s\n", s[i]);
// 		i++;
// 	}
// }

