/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:50:57 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/20 03:39:03 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_exit_status(t_list **head, t_data *data, int *i, char *token)
{
	t_list	*node;

	if (token[*i + 1] != '?')
	{
		node = ft_lstnew(ft_strdup("$"));
		ft_lstadd_back(head, node);
		*i = *i + 1;
	}
	else
	{
		node = ft_lstnew(ft_itoa(g_last_exitstatus));
		ft_lstadd_back(head, node);
		data->status = 1;
		*i = *i + 2;
	}
}

void	dollar(t_data *data, char *token, int *i, t_list **head)
{
	t_list	*node;
	char	*str;
	int		j;

	if (token[*i] == '$')
	{
		j = *i + 1;
		while (token[j] && !is_whitespace(token[j]) && token[j] != '='
			&& token[j] != '\'' && token[j] != '"'
			&& token[j] != '$' && token[j] != '?')
			j++;
		str = ft_substr(token, *i + 1, j - *i - 1);
		if (!*str)
		{
			free(str);
			dollar_exit_status(head, data, i, token);
		}
		else
		{
			node = ft_lstnew(str);
			node->id = 1;
			ft_lstadd_back(head, node);
			*i = j;
		}
	}
}

void	other(char *token, int *i, t_list **head)
{
	t_list	*node;
	char	*str;
	int		j;

	if (token[*i] && token[*i] != '$')
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

void	supp(t_data *data, char	*token, int *i, t_list **head)
{
	while (token[*i])
	{
		dollar(data, token, i, head);
		other(token, i, head);
	}
}

char	*expansion(t_data *data, char *token, t_env **env)
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
	if (token[i])
	{
		supp(data, token, &i, &head);
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
	return (token);
}
