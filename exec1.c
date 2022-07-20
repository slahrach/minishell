/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:47:11 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/19 23:25:26 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_list **f_list)
{
	long long	atoi;
	t_list		*list;

	list = (*f_list)->inside;
	if (ft_lstsize(list) > 1)
	{
		atoi = ft_atoi(list->next->content);
		if (!atoi && ft_strcmp(list->next->content, "0"))
		{
			write(2, "numeric argument required !\n", 28);
			g_last_exitstatus = 255;
		}
		else if (ft_lstsize((list)) > 2)
		{
			write(2, "too many arguments \n", 21);
			g_last_exitstatus = 1;
		}
		else
			g_last_exitstatus = atoi % 256;
	}
	printf("exit\n");
}

void	print_status(t_data *data)
{
	printf("%s : command not found\n", data->f_list->inside->content);
	g_last_exitstatus = 127;
}

int	check_builtins(t_data *data, t_list *tmp)
{
	char	*str;

	if (tmp->arr[0])
	{
		str = ft_strmapi(tmp->arr[0], ft_tolower);
		if (data->f_list->inside->id || !ft_strcmp(str, "echo") || \
		!ft_strcmp(tmp->arr[0], "cd") || !ft_strcmp(tmp->arr[0], "pwd") || \
		!strcmp(tmp->arr[0], "export") || !ft_strcmp(str, "env") || \
		!ft_strcmp(tmp->arr[0], "unset") || !ft_strcmp(tmp->arr[0], "exit"))
			return (0);
		else
			return (1);
	}
	return (3);
}

void	check_builtins_or_other_cmd(t_data *data, t_list *tmp)
{
	if (tmp->arr[0])
	{
		if (data->f_list->inside && data->f_list->inside->id)
			print_status(data);
		else if (!ft_strcmp(tmp->arr[0], "echo"))
			echo_command(&tmp);
		else if (!ft_strcmp(tmp->arr[0], "cd"))
			cd_command(&tmp, &data->env);
		else if (!ft_strcmp(tmp->arr[0], "pwd"))
			pwd_command();
		else if (!strcmp(tmp->arr[0], "export"))
			export_command(&tmp, data->env);
		else if (!ft_strcmp(tmp->arr[0], "env"))
			env_command(&tmp, data->env);
		else if (!ft_strcmp(tmp->arr[0], "unset"))
			unset_command(&tmp, &(data->env));
		else if (!ft_strcmp(tmp->arr[0], "exit"))
			exit_command(&tmp);
		else
			other_commands(data, tmp, data->tool);
	}
}
