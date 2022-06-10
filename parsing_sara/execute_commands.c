/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/10 23:35:50 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_redir *redirect, t_tools *tool)
{
	t_redir	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->id == 1)
		{
			tool->fd_in = open (tmp->content, O_RDONLY);
			if (tool->fd_in == -1)
			{
				printf("bash: %s: No such file or directory\n", tmp->content);
				exit(1);
			}
		}
		else if (tmp->id == 2)
			tool->fd_out = open (tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (tmp->id == 5)
			tool->fd_out = open (tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (tmp->id == 4)
			here_doc(tmp, tool);
		tmp = tmp->next;
	}
}

void	other_commands(t_data *data, t_list *tmp, t_tools *tool)
{
	if (!check_path(tmp->arr[0]) || check_path(tmp->arr[0]) == 2)
		tool->path = ft_strdup(tmp->arr[0]);
	else
		tool->path = find_path(data->env, tmp->arr[0]);
	if (!tool->path)
	{
		write(2, "command not found\n", 25);
		exit(1);
	}
	execve(tool->path, tmp->arr, linked_list_to_table(data->env));
	print_error(tmp->arr[0]);
	exit(1);
}

void	print_error(char *cmd)
{
	char	*err;

	err = strerror (errno);
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
}

int	execute_commands_(t_data *data, t_list *tmp)
{
	int		pid;

	if (pipe(data->tool->p) == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		close(data->tool->p[0]);
		dup2(data->tool->p[1], 1);
		close(data->tool->p[1]);
		if (tmp->redirect)
			check_redirections(tmp->redirect, data->tool);
		dup2(data->tool->fd_in, 0);
		close (data->tool->fd_in);
		dup2(data->tool->fd_out, 1);
		close (data->tool->fd_out);
		if (!check_builtins(data, tmp))
		{
			check_builtins_or_other_cmd(data, tmp);
			exit(0);
		}
		else
		{
			check_builtins_or_other_cmd(data, tmp);
			exit (1);
		}
	}
	else
	{
		close(data->tool->p[1]);
		dup2(data->tool->p[0], 0);
		close(data->tool->p[0]);
	}
	return (pid);
}

int	execute_last_command(t_data *data, t_list *tmp)
{
	int		pid;

	if (pipe(data->tool->p) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (tmp->redirect)
		check_redirections(tmp->redirect, data->tool);
	if (pid == 0)
	{
		dup2(data->tool->fd_in, 0);
		close (data->tool->fd_in);
		dup2(data->tool->fd_out, 1);
		close (data->tool->fd_out);
		if (!check_builtins(data, tmp))
		{
			check_builtins_or_other_cmd(data, tmp);
			//exit(0);
		}
		else
		{
			check_builtins_or_other_cmd(data, tmp);
			exit (1);
		}
	}
	else
		close (data->tool->fd_out);
	return (pid);
}

void	close_n_wait(t_tools *tool, int *pid)
{
	int		i;

	i = 0;
	close(tool->p[0]);
	close(tool->p[1]);
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	execute_commands(t_data *data)
{
	t_list	*tmp;
	int		*pid;
	int		i;
	int		fd_in;
	int		fd_out;

	tmp = data->f_list;
	i = 0;
	fd_in = dup(0);
	fd_out = dup(1);
	pid = malloc (sizeof(int) * ft_lstsize(tmp));
	data->tool = malloc (sizeof(t_tools));
	data->tool->fd_in = dup(0);
	data->tool->fd_out = dup(1);
	while (tmp->next)
	{
		pid[i++] = execute_commands_(data, tmp);
		tmp = tmp->next;
	}
	puts("------+---------");
	pid[i] = execute_last_command(data, tmp);
	close_n_wait(data->tool, pid);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	// exit_status_command(&data);
}
