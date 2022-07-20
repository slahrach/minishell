/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 22:32:37 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 22:34:45 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_herdocs_num(t_data *data)
{
	if (how_many_heredocs_we_have(data) > 16)
	{
		printf("maximum here-document count exceeded\n");
		g_last_exitstatus = 2;
		exit (g_last_exitstatus);
	}
}

void	other_commands(t_data *data, t_list *tmp, t_tools *tool)
{
	if (!check_path(tmp->arr[0]) || check_path(tmp->arr[0]) == 2)
		tool->path = ft_strdup(tmp->arr[0]);
	else
		tool->path = find_path(&data->env, tmp->arr[0]);
	if (!tool->path)
	{
		if (!data->env->flag_unset_path)
			printf("bash: %s: command not found\n", tmp->arr[0]);
		g_last_exitstatus = 127;
		return ;
	}
	execve(tool->path, tmp->arr, linked_list_to_table(data->env));
	free (tool->path);
	print_error(tmp->arr[0]);
}

int	builtin_or_other_cmd(t_data *data, t_list *tmp)
{
	if (tmp->arr[0])
	{
		if (data->f_list->inside->id)
			return (1);
		else if (!ft_strcmp(tmp->arr[0], "echo"))
			return (2);
		else if (!ft_strcmp(tmp->arr[0], "cd"))
			return (3);
		else if (!ft_strcmp(tmp->arr[0], "pwd"))
			return (4);
		else if (!strcmp(tmp->arr[0], "export"))
			return (5);
		else if (!ft_strcmp(tmp->arr[0], "env"))
			return (6);
		else if (!ft_strcmp(tmp->arr[0], "unset"))
			return (7);
		else if (!ft_strcmp(tmp->arr[0], "exit"))
			return (8);
	}
	return (0);
}
