/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:51 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/11 00:20:52 by slahrach         ###   ########.fr       */
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
	redir_add_back(&(*head)->redirect, redir_new(content, (*list)->id));
	(*list) = (*list)->next->next;
	return (0);
}

static void	cmds(t_list **list, t_list **head)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup((*list)->content));
	if ((*list)->id == STATUS)
		new->id = 1;
	ft_lstadd_back(&((*head)->inside), new);
	(*list) = (*list)->next;
}

t_list	*devide(t_data *data, t_list **list_free)
{
	t_list	*list;
	t_list	*head;
	t_list	*temp;

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
		else if (list->id == 0 || list->id == STATUS)
			cmds(&list, &head);
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
