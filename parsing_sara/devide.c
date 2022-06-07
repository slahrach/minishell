/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:51 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/07 04:31:06 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_arr(t_list **head)
{
	int		i;
	int		l;
	t_list	*temp_head;
	t_list	*temp;

	temp_head = *head;
	while (temp_head)
	{
		temp = temp_head->inside;
		i = 0;
		l = ft_lstsize(temp);
		temp_head->arr = malloc ((l + 1) * sizeof (char *));
		while (temp)
		{
			temp_head->arr[i] = ft_strdup(temp->content);
			i++;
			temp = temp->next;
		}
		temp_head->arr[i] = NULL;
		temp_head = temp_head->next;
	}
}

static int	t_pipe(t_data *data, t_list **list, t_list **head)
{
	if (!(*head) || !(*list)->next)
	{
		error(data, 0);
		return (1);
	}
	(*list) = (*list)->next;
	(*head)->pipe_after = 1;
	ft_lstadd_back(head, _new());
	(*head) = (*head)->next;
	(*head)->pipe_before = 1;
	return (0);
}

static int	check(t_data *data, t_list **list, t_list **head)
{
	char	*content;

	if (!(*list)->next)
	{
		error(data, 0);
		return (1);
	}
	content = ft_strdup((*list)->next->content);
	if ((*list)->next->id)
	{
		error(data, 0);
		return (1);
	}
	if ((*list)->id == INPUT)
		redir_add_back(&(*head)->infile, redir_new(content));
	else if ((*list)->id == OUTPUT)
		redir_add_back(&(*head)->outfile, redir_new(content));
	else if ((*list)->id == DELIMITER)
		redir_add_back(&(*head)->delimiter, redir_new(content));
	else if ((*list)->id == APPEND)
		redir_add_back(&(*head)->append, redir_new(content));
	(*list) = (*list)->next->next;
	return (0);
}

t_list	*devide(t_data *data, t_list **list_free)
{
	t_list	*list;
	t_list	*head;
	t_list	*temp;
	char	*content;

	list = *list_free;
	head = _new();
	temp = head;
	while (list)
	{
		if (list->id == PIPE)
		{
			if (t_pipe (data, &list, &head))
				break ;
		}
		else if (list->id == 0)
		{
			content = ft_strdup(list->content);
			ft_lstadd_back(&(head->inside), ft_lstnew(content));
			list = list->next;
		}
		else
		{
			if (check(data, &list, &head))
				break ;
		}
	}
	make_arr(&temp);
	ft_lstclear(list_free);
	return (temp);
}
