/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:54:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/11 00:01:11 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*remove_quotes(int *i, char *line, t_env *env, t_data *data)
{
	int		j;
	char	*str1;

	j = ft_strchr1(line + (*i) + 1, line[*i]);
	if (j == -1)
	{
		error(data, 1);
		(*i)++;
		return (NULL);
	}
	str1 = ft_substr(line, (*i) + 1, j);
	if (line[*i] == '"')
		str1 = expansion(data, str1, env);
	*i += j + 2;
	return (str1);
}

char	*handle_quoting(int	*i, char *line, t_data *data, t_env *env)
{
	t_list	**list;
	char	*str2;
	char	*str1;

	list = &data->list_token;
	if (line [*i] && (line[*i] == '"' || line[*i] == '\''))
	{
		str1 = remove_quotes(i, line, env, data);
		if (!str1)
			return (NULL);
		if (is_special(line[*i]))
		{
			ft_lstadd_back(list, ft_lstnew(str1));
			non_quoting(i, line, data, env);
			return (NULL);
		}
		str2 = non_quoting(i, line, data, env);
		if (str2)
			str1 = ft_strjoin2(str1, str2);
		return (str1);
	}
	return (NULL);
}

char	*non_quoting(int *i, char *line, t_data *data, t_env *env)
{
	t_list	**list;
	int		id;
	char	*str1;
	char	*str2;
	int		j;

	list = &data->list_token;
	if (line[*i] && !is_whitespace(line[*i]))
	{
		id = is_special(line[*i]);
		if (check_special(i, line, id, list))
			return (NULL);
		j = *i;
		while (line[j] && !is_whitespace(line[j]) && !is_special(line[j])
			&& line[j] != '"' && line[j] != '\'')
			j++;
		str1 = ft_substr(line, *i, j - (*i));
		str1 = expansion(data, str1, env);
		*i = j;
		str2 = handle_quoting(i, line, data, env);
		if (str2)
			str1 = ft_strjoin2(str1, str2);
		return (str1);
	}
	return (NULL);
}

void	call(t_data *data, char *str, t_list **list)
{
	t_list	*new;

	if (str)
	{
		new = ft_lstnew(str);
		if (data->status)
		{
			new->id = STATUS;
			data->status = 0;
		}
		ft_lstadd_back(list, new);
	}
}

void	tokenize(char *line_t, t_data *data, t_env *env)
{
	t_list	**list;
	char	*line;
	char	*str;
	int		i;

	list = &data->list_token;
	i = 0;
	*list = NULL;
	line = ft_strtrim(line_t, "\n\f\t\v\r ");
	free(line_t);
	while (line[i])
	{
		str = handle_quoting(&i, line, data, env);
		call(data, str, list);
		str = non_quoting(&i, line, data, env);
		call(data, str, list);
		if (is_whitespace(line[i]))
			i++;
	}
	free(line);
}
