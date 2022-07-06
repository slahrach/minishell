/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 01:15:01 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/06 01:29:21 by iouardi          ###   ########.fr       */
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

static void	free_multi(char	**ptr, int j)
{
	while (j > 0)
	{
		free(ptr[j - 1]);
		j--;
	}
	free(ptr);
}

static void	fill_1(char	**ptr, int r, char const *s, int i)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		ptr[j++] = ft_strdup(s);
		ptr[j] = NULL;
		return ;
	}
	ptr[0] = ft_strndup(s, r);
	ptr[1] = ft_strdup(ft_strchr(s, '=') + 1);
	while (j < 2)
	{
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
	fill_1 (ptr, r, s, i);
	return (ptr);
}
