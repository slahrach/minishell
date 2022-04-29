/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:54:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/29 03:22:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(char *token)
{
	int		j;
	int		i;
	char	*result = NULL;
	t_list	*head;
	t_list	*temp;
	t_list	*node;
	char	*str;

	i = 0;
	head = NULL;
	if (!token || !*token)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '$')
		{
			j = i + 1;
			while (token[j] && !is_whitespace(token[j])
				&& token[j] != '\'' && token[j] != '"')
				j++;
			str = ft_substr(token, i + 1, j - i - 1);
			if (!*str)
			{
				node = ft_lstnew("$");
				node->id = 0;
				ft_lstadd_back(&head, node);
			}
			else
			{
				node = ft_lstnew(str);
				node->id = 1;
				ft_lstadd_back(&head, node);
			}
			i = j;
		}
		else
		{
			j = i;
			while (token[j] && token[j] != '$')
				j++;
			str = ft_substr(token, i, j - i);
			node = ft_lstnew(str);
			node->id = 0;
			ft_lstadd_back(&head, node);
			i = j;
		}
	}
	temp = head;
	while (temp)
	{
		if (temp->id)
		{
			if (!ft_strcmp(temp->content, "?"))
				temp->content = ft_strdup("$?");
			else
				temp->content = ft_strdup(getenv(temp->content));
		}
		temp = temp->next;
	}
	while (head)
	{
		result = ft_strjoin(result, head->content);
		head = head->next;
	}
	return (result);
}

char	*handle_quoting(int	*i, char *line, t_list **list)
{
	char	*str1;
	int		j;

	if (line[*i] == '"' || line[*i] == '\'')
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
		str1 = ft_strjoin(str1, non_quoting(i, line, list));
		return (str1);
	}
	return (NULL);
}

char	*non_quoting(int *i, char *line, t_list **list)
{
	t_list	*new;
	int		id;
	char	*str1;
	int		j;

	if (!is_whitespace(line[*i]))
	{
		id = is_special(line[*i]);
		if (id)
		{
			if (id == 1 && line[*i + 1] && line[*i + 1] == '<')
			{
				new = ft_lstnew("<<");
				new->id = DELIMITER;
				(*i) += 2;
			}
			else if (id == 2 && line[*i + 1] && line[*i + 1] == '>')
			{
				new = ft_lstnew(">>");
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
			return (NULL);
		}
		j = *i;
		while (line[j] && !is_whitespace(line[j]) && !is_special(line[j])
			&& line[j] != '"' && line[j] != '\'')
			j++;
		str1 = ft_substr(line, *i, j - (*i));
		str1 = expansion(str1);
		*i = j;
		str1 = ft_strjoin(str1, handle_quoting(i, line, list));
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
