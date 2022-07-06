/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 02:23:06 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/06 02:23:39 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_head(t_env **env, char *name)
{
	t_env	*after_node;
	t_env	*copy;

	copy = *env;
	if (!ft_strcmp(copy->name, name))
	{
		after_node = copy;
		copy = copy->next;
		free(after_node->name);
		free(after_node->value);
		free(after_node);
		*env = copy;
		return (0);
	}
	return (1);
}

void	unset_node_supp(t_env **copy, char *name, int *sign)
{
	t_env	*after_node;
	t_env	*before_node;

	while (copy)
	{
		if (!*sign)
		{
			before_node = (*copy);
			*sign = 1;
		}
		if (!ft_strcmp(name, (*copy)->name))
		{
			if (!(*copy)->next)
				after_node = NULL;
			else
				after_node = (*copy)->next;
			free((*copy)->name);
			free((*copy)->value);
			free((*copy));
			before_node->next = after_node;
			return ;
		}
		before_node = (*copy);
		(*copy) = (*copy)->next;
	}
}

void	unset_node(t_env **env, char *name)
{
	t_env	*copy;
	int		sign;

	copy = *env;
	sign = 0;
	if (!unset_head(env, name))
		return ;
	unset_node_supp(&copy, name, &sign);
}
