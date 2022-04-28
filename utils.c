/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:00:36 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 20:07:39 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*find_prompt(void)
{
	const char	*folder = NULL;
	const char	*user = NULL;
	const char	*prompt = NULL;

	folder = getenv("PWD");
	user = getenv("USER");
	if (ft_strrchr(folder, '/'))
		folder = ft_strrchr(folder, '/') + 1;
	folder = (const char *) ft_strjoin ("\033[1;33m", folder);
	folder = (const char *) ft_strjoin (folder, "\033[0m");
	if (ft_strchr(user, '='))
		user = ft_strchr(user, '=') + 1;
	user = (const char *) ft_strjoin ("\033[1;31m", user);
	user = (const char *) ft_strjoin (user, "\033[0m");
	prompt = (const char *) ft_strjoin ("\033[1;33m* {\033[0m", user);
	prompt = (const char *) ft_strjoin (prompt, "\033[1;33m} \033[0m");
	prompt = (const char *) ft_strjoin (prompt, folder);
	prompt = (const char *) ft_strjoin (prompt, "\033[1;31m $ \033[0m");
	return (prompt);
}

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

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
			while (token[j] && !is_whitespace(token[j]))
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

void	to_parse(char *line, t_list **list)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	line = ft_strtrim(line, "\n\f\t\v\r ");
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = ft_strchr1(line + i + 1, line[i]);
			if (j == -1)
				error(0);
			str = ft_substr(line, i + 1, j);
			if (line[i] == '"')
				str = expansion(str);
			if (str && *str)
				ft_lstadd_back(list, ft_lstnew(str));
			i += j + 2;
		}
		else if (!is_whitespace(line[i]))
		{
			j = i;
			while (line[j] && !is_whitespace(line[j]))
				j++;
			str = ft_substr(line, i, j - i);
			str = expansion(str);
			if (str)
				ft_lstadd_back(list, ft_lstnew(str));
			i = j;
		}
		else
			i++;
	}
}
//!!!handle ------per"sonna"ge---------case && ------'"'ls'"'-----------case
