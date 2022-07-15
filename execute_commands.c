/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/15 12:35:38 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd)
{
	char	*err;

	err = strerror (errno);
	printf ("bash: %s: %s\n", cmd, err);
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
	print_error(tmp->arr[0]);
}

int	execute_commands_(t_data *data, t_list *tmp)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(1);
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
		close (tmp->fd_in);
		close (tmp->fd_out);
		if (tmp->arr[0] && !ft_strcmp(tmp->arr[0], "exit"))
			exit_command(data, &tmp);
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
			exit (g_last_exitstatus);
		return (1);
	}
	return (0);
}

void	execute_commands(t_data *data)
{
	t_list	*tmp;
	int		*pid;
	int		fd_in;
	int		fd_out;
	int		i;

	tmp = data->f_list;
	i = 0;
	fd_in = dup(0);
	fd_out = dup(1);
	pid = malloc (sizeof(int) * ft_lstsize(tmp));
	data->tool = malloc (sizeof(t_tools));
	if (execute_one_builtin(data, tmp))
		return ;
	tmp = data->f_list;
	check_pipes(data, &data->f_list, data->tool);
	while (tmp)
	{
		pid[i++] = execute_commands_(data, tmp);
		tmp = tmp->next;
	}
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_n_wait(data->tool, pid);
}
