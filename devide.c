/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:51 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/14 04:47:34 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new(void)
{
	t_list	*new;

	new = malloc (sizeof (t_list));
	new->inside = NULL;
	new->next = NULL;
	return (new);
}

t_list	*devide(t_list *list)
{
	t_list	*head;
	t_list	*temp;

	head = new();
	temp = head;
	while (list)
	{
		if (list->id == PIPE)
		{
			if (!head || !list->next)
				error(4);
			list = list->next;
			head->pipe_after = 1;
			ft_lstadd_back(&head, new());
			head = head->next;
			head->pipe_before = 1;
		}
		else if (list->id == 0)
		{
			ft_lstadd_back(&(head->inside), ft_lstnew(ft_strdup(list->content)));
			list = list->next;
		}
		else if (list->id == INPUT)
		{
			if (!list->next)
				error(4);
			head->infile = ft_strdup(list->next->content);
			list = list->next->next;
		}
		else if (list->id == OUTPUT)
		{
			if (!list->next)
				error(4);
			head->output = ft_strdup(list->next->content);
			list = list->next->next;
		}
		else if (list->id == DELIMITER)
		{
			if (!list->next)
				error(4);
			head->delimiter = ft_strdup(list->next->content);
			list = list->next->next;
		}
		else if (list->id == APPEND)
		{
			if (!list->next)
				error(4);
			head->append = ft_strdup(list->next->content);
			list = list->next->next;
		}
	}
	return (temp);
}
