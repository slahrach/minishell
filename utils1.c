/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:51:52 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 03:39:42 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	already_exists_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	env_add_change2(t_env **env, char *name, int flag)
{
	t_env	*copy;

	copy = *env;
	while (copy)
	{
		if (name && copy->name && !ft_strcmp(name, copy->name))
		{
			if (!already_exists_oldpwd(*env))
			{
				add_back(env, new_node("OLDPWD", copy->value, copy->flag));
				return ;
			}
			else
			{
				env_add_change1(env, "OLDPWD", copy->value, flag);
				return ;
			}
		}
		copy = copy->next;
	}
}

void	print_error(char *cmd)
{
	char	*err;

	err = strerror (errno);
	printf ("bash: %s: %s\n", cmd, err);
}

int	check_here_doc(t_list *f_list)
{
	t_redir	*tmp;

	tmp = f_list->redirect;
	while (tmp)
	{
		if (tmp->id == 4)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	change(t_list **head, t_env **env)
{
	char	*str;
	t_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp->id)
		{
			str = ft_strdup(temp->content);
			free(temp->content);
			temp->content = ft_strdup(ft_getenv(env, str));
			free(str);
		}
		temp = temp->next;
	}
}
