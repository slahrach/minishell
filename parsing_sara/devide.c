/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:51 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/07 22:45:22 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new(void)
{
	t_list	*new;

	new = malloc (sizeof (t_list));
	new->inside = NULL;
	new->exit_status = 0;
	new->next = NULL;
	new->pipe_after = 0;
	new->pipe_before = 0;
	new->redirect = NULL;
	new->arr = NULL;
	new->content = NULL;
	return (new);
}

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

static void	t_pipe(t_list **list, t_list **head)
{
	if (!(*head) || !(*list)->next)
		error(4);
	(*list) = (*list)->next;
	(*head)->pipe_after = 1;
	ft_lstadd_back(head, new());
	(*head) = (*head)->next;
	(*head)->pipe_before = 1;
}

static void	check(t_list **list, t_list **head)
{
	char	*content;

	if (!(*list)->next)
		error(4);
	content = ft_strdup((*list)->next->content);
	redir_add_back(&(*head)->redirect, redir_new(content, (*list)->id));
	(*list) = (*list)->next->next;
}

t_list	*devide(t_list **list_free)
{
	t_list	*list;
	t_list	*head;
	t_list	*temp;
	char	*content;

	list = *list_free;
	head = new();
	temp = head;
	while (list)
	{
		if (list->id == PIPE)
			t_pipe (&list, &head);
		else if (list->id == 0)
		{
			content = ft_strdup(list->content);
			ft_lstadd_back(&(head->inside), ft_lstnew(content));
			list = list->next;
		}
		else
			check(&list, &head);
	}
	make_arr(&temp);
	ft_lstclear(list_free);
	return (temp);
}
