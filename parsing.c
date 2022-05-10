/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:54:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/10 19:32:30 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quoting(int	*i, char *line, t_list **list)
{
	char	*str2;
	char	*str1;
	int		j;

	if (line [*i] && (line[*i] == '"' || line[*i] == '\''))
	{
		j = ft_strchr1(line + (*i) + 1, line[*i]);
		if (j == -1)
			error(0);
		str1 = ft_substr(line, (*i) + 1, j);
		if (line[*i] == '"')
			str1 = expansion(str1);
		*i += j + 2;
		if (is_special(line[*i]))
		{
			ft_lstadd_back(list, ft_lstnew(str1));
			non_quoting(i, line, list);
			return (NULL);
		}
		str2 = non_quoting(i, line, list);
		str1 = ft_strjoin1(str1, str2);
		free(str2);
		return (str1);
	}
	return (NULL);
}

int	check_special(int *i, char *line, int id, t_list **list)
{
	t_list	*new;

	if (id)
	{
		if (id == 1 && line[*i + 1] && line[*i + 1] == '<')
		{
			new = ft_lstnew(ft_strdup("<<"));
			new->id = DELIMITER;
			(*i) += 2;
		}
		else if (id == 2 && line[*i + 1] && line[*i + 1] == '>')
		{
			new = ft_lstnew(ft_strdup(">>"));
			new->id = APPEND;
			(*i) += 2;
		}
		else
		{
			new = ft_lstnew(chr_to_str(line[*i]));
			new->id = id;
			(*i) += 1;
		}
		ft_lstadd_back(list, new);
	}
	return (id);
}

char	*non_quoting(int *i, char *line, t_list **list)
{
	int		id;
	char	*str1;
	char	*str2;
	int		j;

	if (!is_whitespace(line[*i]) && line[*i])
	{
		id = is_special(line[*i]);
		if (check_special(i, line, id, list))
			return (NULL);
		j = *i;
		while (line[j] && !is_whitespace(line[j]) && !is_special(line[j])
			&& line[j] != '"' && line[j] != '\'')
			j++;
		str1 = ft_substr(line, *i, j - (*i));
		str1 = expansion(str1);
		*i = j;
		str2 = handle_quoting(i, line, list);
		str1 = ft_strjoin1(str1, str2);
		free(str2);
		return (str1);
	}
	return (NULL);
}

void	to_parse(char *line, t_list **list)
{
	char	*str;
	int		i;

	i = 0;
	line = ft_strtrim(line, "\n\f\t\v\r ");
	while (line[i])
	{
		str = handle_quoting(&i, line, list);
		if (str)
			ft_lstadd_back(list, ft_lstnew(str));
		str = non_quoting(&i, line, list);
		if (str)
			ft_lstadd_back(list, ft_lstnew(str));
		if (is_whitespace(line[i]))
			i++;
	}
}
