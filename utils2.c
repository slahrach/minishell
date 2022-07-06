/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 23:39:53 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/06 03:47:15 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special(int *i, char *line, int id, t_list **list)
{
	t_list	*new;

	if (id)
	{
		if (id == 1 && line[*i + 1] && line[*i + 1] == '<')
		{
			new = ft_lstnew(ft_strdup("<<"));
			new->id = DELIMITER;
			(*i) += 2;
		}
		else if (id == 2 && line[*i + 1] && line[*i + 1] == '>')
		{
			new = ft_lstnew(ft_strdup(">>"));
			new->id = APPEND;
			(*i) += 2;
		}
		else
		{
			new = ft_lstnew(chr_to_str(line[*i]));
			new->id = id;
			(*i) += 1;
		}
		ft_lstadd_back(list, new);
	}
	return (id);
}

char	**linked_list_to_table(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	tmp = env;
	i = 0;
	arr = malloc(sizeof(char *) * ft_lstsize_env(tmp));
	while (tmp)
	{
		arr[i] = ft_strjoin(tmp->name, "=");
		arr[i] = ft_strjoin(arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = 0;
	return (arr);
}

int	ft_lstsize_env(t_env *lst)
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

void	free_all(char **cmd_temp1)
{
	int		i;

	i = 0;
	while (cmd_temp1[i])
	{
		free (cmd_temp1[i]);
		cmd_temp1[i] = NULL;
		i++;
	}
	free (cmd_temp1);
}
