/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 23:54:52 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/19 01:37:17 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_node(char *name, char *value)
{
	t_env	*new;

	new = malloc (sizeof(t_env));
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	sizelst(t_env *lst)
{
	t_env	*temp;
	int		i;

	if (!lst)
		return (0);
	i = 1;
	temp = lst;
	while (temp->next)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	add_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!(*lst))
	{
		add_front(lst, new);
		return ;
	}
	last = find_last(*lst);
	if (new->next == NULL)
		last->next = new;
	while (new->next != NULL)
	{
		last->next = new;
		new = new->next;
	}
}

void	add_front(t_env **lst, t_env *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

t_env	*find_last(t_env *lst)
{
	t_env	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}
