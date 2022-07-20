/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 05:41:56 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute_commands_(t_data *data, t_list *tmp)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		printf ("pipe failed\n");
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(tmp->fd_in, 0);
		dup2(tmp->fd_out, 1);
		close(data->tool->p[0]);
		check_builtins_or_other_cmd(data, tmp);
		exit(g_last_exitstatus);
	}
	else
	{
		if (tmp->fd_in != 0)
		{
			close (tmp->fd_in);
			tmp->fd_in = 0;
		}
		if (tmp->fd_out != 1)
		{
			close (tmp->fd_out);
			tmp->fd_out = 1;
		}
		if (tmp->arr[0] && !ft_strcmp(tmp->arr[0], "exit"))
			exit_command(&tmp);
	}
	return (pid);
}

int	execute_one_builtin(t_data *data, t_list *tmp)
{
	if (!data->f_list->pipe_after && \
		builtin_or_other_cmd(data, tmp) && !tmp->redirect)
	{	
		check_builtins_or_other_cmd(data, tmp);
		if (!ft_strcmp(tmp->arr[0], "exit"))
		{
			clear_env(&data->env);
			exit (g_last_exitstatus);
		}
		return (1);
	}
	return (0);
}

int	execute_commands_supp(t_data *data, t_list *tmp, int *pid)
{
	if (execute_one_builtin(data, tmp))
	{
		free (pid);
		return (1);
	}
	if (check_pipes(data, &data->f_list, data->tool))
		return (1);
	return (0);
}

void	execute_commands(t_data *data)
{
	t_list	*tmp;
	int		*pid;
	int		i;

	i = 0;
	tmp = data->f_list;
	pid = malloc (sizeof(int) * ft_lstsize(tmp));
	if (execute_commands_supp(data, tmp, pid))
		return ;
	if (!data->signal_flag)
		return ;
	tmp = data->f_list;
	while (tmp)
	{
		pid[i++] = execute_commands_(data, tmp);
		if (pid[i] == -1)
			break ;
		tmp = tmp->next;
	}
	close_n_wait(data->tool, pid);
	free (pid);
}
