/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:48:53 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/18 17:47:52 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	i = 0;
	str = malloc ((ft_strlen (s1) + ft_strlen (s2) + 1) * sizeof(char));
	while (*s1 != '\0')
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin0(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	else if (!s2)
		s2 = ft_strdup("");
	i = -1;
	str = malloc ((ft_strlen (s1) + ft_strlen (s2) + 1) * sizeof(char));
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s2);
	return (str);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	else if (!s2)
		s2 = ft_strdup("");
	i = -1;
	str = malloc ((ft_strlen (s1) + ft_strlen (s2) + 1) * sizeof(char));
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	else if (!s2)
		s2 = ft_strdup("");
	i = -1;
	str = malloc ((ft_strlen (s1) + ft_strlen (s2) + 1) * sizeof(char));
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
