/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:47:11 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/07 22:50:01 by slahrach         ###   ########.fr       */
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

int	check_builtins(t_list *tmp)
{
	char	*str;

	str = ft_strmapi(tmp->arr[0], ft_tolower);
	if (!ft_strcmp(tmp->arr[0], "$?") || !ft_strcmp(str, "echo") || \
	!ft_strcmp(tmp->arr[0], "cd") || !ft_strcmp(tmp->arr[0], "pwd") || \
	!strcmp(tmp->arr[0], "export") || !ft_strcmp(str, "env") || \
	!ft_strcmp(tmp->arr[0], "unset") || !ft_strcmp(tmp->arr[0], "exit"))
		return (0);
	else
		return (1);
}

void	check_builtins_or_other_cmd(t_data *data, t_list *tmp)
{
	char	*str;

	str = ft_strmapi(tmp->arr[0], ft_tolower);
	if (!ft_strcmp(tmp->arr[0], "$?"))
		print_status(&data);
	if (!ft_strcmp(str, "echo"))
		echo_command(&tmp);
	else if (!ft_strcmp(tmp->arr[0], "cd"))
		cd_command(&tmp, data->env);
	else if (!ft_strcmp(tmp->arr[0], "pwd"))
		pwd_command(&tmp);
	else if (!strcmp(tmp->arr[0], "export"))
		export_command(&tmp, data->env);
	else if (!ft_strcmp(str, "env"))
		env_command(&tmp, data->env);
	else if (!ft_strcmp(tmp->arr[0], "unset"))
		unset_command(&tmp, data->env);
	else if (!ft_strcmp(tmp->arr[0], "exit"))
		exit_command(&tmp);
	else
		other_commands(data, tmp, data->tool);
}
