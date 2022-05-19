/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:50:57 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/19 03:01:32 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar(char *token, int *i, t_list **head)
{
	t_list	*node;
	char	*str;
	int		j;

	if (token[*i] == '$')
	{
		j = *i + 1;
		while (token[j] && !is_whitespace(token[j])
			&& token[j] != '\'' && token[j] != '"')
			j++;
		str = ft_substr(token, *i + 1, j - *i - 1);
		if (!*str)
		{
			free(str);
			node = ft_lstnew(ft_strdup("$"));
			ft_lstadd_back(head, node);
		}
		else
		{
			node = ft_lstnew(str);
			node->id = 1;
			ft_lstadd_back(head, node);
		}
		*i = j;
	}
}

void	other(char *token, int *i, t_list **head)
{
	t_list	*node;
	char	*str;
	int		j;

	if (token[*i] != '$')
	{
		j = *i;
		while (token[j] && token[j] != '$')
			j++;
		str = ft_substr(token, *i, j - *i);
		node = ft_lstnew(str);
		node->id = 0;
		ft_lstadd_back(head, node);
		*i = j;
	}
}

void	change(t_list **head, t_env *env)
{
	char	*str;
	t_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->id)
		{
			if (!ft_strcmp(temp->content, "?"))
			{
				free(temp->content);
				temp->content = ft_strdup("$?");
			}
			else
			{
				str = ft_strdup(temp->content);
				free(temp->content);
				temp->content = ft_strdup(ft_getenv(env, str));
				free(str);
			}
		}
		temp = temp->next;
	}
}

char	*expansion(char *token, t_env *env)
{
	int		i;
	char	*result;
	t_list	*head;
	t_list	*temp;

	i = 0;
	head = NULL;
	result = NULL;
	if (!token)
		return (NULL);
	while (token[i])
	{
		dollar(token, &i, &head);
		other(token, &i, &head);
	}
	change(&head, env);
	temp = head;
	while (temp)
	{
		result = ft_strjoin1(result, temp->content);
		temp = temp->next;
	}
	free(token);
	ft_lstclear(&head);
	return (result);
}
