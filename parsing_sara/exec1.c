/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:47:11 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/07 01:24:22 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_sara/minishell.h"

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
			(*f_list)->exit_status = 255;
		}
		else if (ft_lstsize(list) > 2)
		{
			write(2, "too many arguments \n", 21);
			(*f_list)->exit_status = 1;
		}
		else
			(*f_list)->exit_status = atoi % 256;
	}
	printf("exit\n");
	//exit(0);
}

void	exit_status_command(t_data **data)
{
	t_list	*list;

	list = (*data)->f_list;
	while (list)
	{
		if (list->exit_status)
		{
			(*data)->last_exitstatus = list->exit_status;
			return ;
		}
		(*data)->last_exitstatus = 0;
		list = list->next;
	}
}

void	print_status(t_data **data)
{
	printf("%d : command not found\n", (*data)->last_exitstatus);
	(*data)->f_list->exit_status = 127;
}

void	execute_commands(t_data *data)
{
	char	*str;

	if (data->f_list && data->f_list->arr[0])
	{
		str = ft_strmapi(data->f_list->arr[0], ft_tolower);
		if (!ft_strcmp(data->f_list->arr[0], "$?"))
			print_status(&data);
		if (!ft_strcmp(str, "echo"))
			echo_command(&data->f_list);
		else if (!ft_strcmp(data->f_list->arr[0], "cd"))
			cd_command(&data->f_list, data->env);
		else if (!ft_strcmp(data->f_list->arr[0], "pwd"))
			pwd_command(&data->f_list);
		else if (!strcmp(data->f_list->arr[0], "export"))
			export_command(&data->f_list, data->env);
		else if (!ft_strcmp(str, "env"))
			env_command(&data->f_list, data->env);
		else if (!ft_strcmp(data->f_list->arr[0], "unset"))
			unset_command(&data->f_list, data->env);
		else if (!ft_strcmp(data->f_list->arr[0], "exit"))
			exit_command(&data->f_list);
	}
	exit_status_command(&data);
}
