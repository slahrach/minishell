/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/27 20:34:12 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int fd)
{
	if (fd != 0 && fd != 1)
		close (fd);
}

void	check_redirections(t_data *data, t_redir *redirect, t_tools *tool)
{
	t_redir *tmp;

	tmp = redirect;
	while (tmp)
	{
		if (tmp->id == 1)
		{
			close_fds(tool->fd_in);
			tool->fd_in = open (tmp->content, O_RDONLY);
			if (tool->fd_in == -1)
			{
				printf("bash: %s: No such file or directory\n", tmp->content);
				exit(1);
			}
		}
		else if (tmp->id == 2)
		{
			close_fds(tool->fd_out);
			tool->fd_out = open (tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		}
		else if (tmp->id == 5)
		{
			close_fds(tool->fd_out);
			tool->fd_out = open (tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
		}
		else if (tmp->id == 4)
		{
			here_doc(tmp, tool);
			if (data->error)
			{
				printf("Error\nsyntax error !\n");
				g_last_exitstatus = 258;
			}
		}
		tmp = tmp->next;
	}
}

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
		tool->path = find_path(data->env, tmp->arr[0]);
	if (!tool->path)
	{
		printf("bash: %s: command not found\n", tmp->arr[0]);
		exit(1);
	}
	execve(tool->path, tmp->arr, linked_list_to_table(data->env));
	print_error(tmp->arr[0]);
	exit(1);
}

int	execute_commands_(t_data *data, t_list *tmp)
{
	int		pid;

	if (pipe(data->tool->p) == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
	{
		// if (tmp->id != 4)
		// {
		// 	close(data->tool->p[0]);
		// 	dup2(data->tool->p[1], 1);
		// 	close(data->tool->p[1]);
		// }
		char	grr[100];
		if (tmp->redirect)
			check_redirections(data, tmp->redirect, data->tool);
		read(data->tool->fd_in, grr, 100);
		printf("%s", grr);
		write (2, grr, 100);
		write (2, "\n", 1);
		exit (0);
		dup2(data->tool->fd_in, 0);
		close (data->tool->fd_in);
		dup2(data->tool->fd_out, 1);
		close (data->tool->fd_out);
		check_builtins_or_other_cmd(data, tmp);
		exit (1);
	}
	else
	{
		exit_status_command(data);
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
	if (pid == 0)
	{
		if (tmp->redirect)
			check_redirections(data, tmp->redirect, data->tool);
		dup2(data->tool->fd_in, 0);
		close (data->tool->fd_in);
		dup2(data->tool->fd_out, 1);
		close (data->tool->fd_out);
		check_builtins_or_other_cmd(data, tmp);
		exit(0);
	}
	else
	{
		close (data->tool->fd_out);
		exit_status_command(data);
		if (tmp->arr[0])
			if (!ft_strcmp(tmp->arr[0], "exit"))
				exit(g_last_exitstatus);
	}
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
//new
int builtin_or_other_cmd(t_data *data, t_list *tmp)
{
	char	*str;

	if (tmp->arr[0])
	{
		str = ft_strmapi(tmp->arr[0], ft_tolower);
		if (data->f_list->inside->id)
			return (1);
		else if (!ft_strcmp(str, "echo"))
			return (2);
		else if (!ft_strcmp(tmp->arr[0], "cd"))
			return (3);
		else if (!ft_strcmp(tmp->arr[0], "pwd"))
			return (4);
		else if (!strcmp(tmp->arr[0], "export"))
			return (5);
		else if (!ft_strcmp(str, "env"))
			return (6);
		else if (!ft_strcmp(tmp->arr[0], "unset"))
			return (7);
		else if (!ft_strcmp(tmp->arr[0], "exit"))
			return (8);
	}
	return (0);
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
	//new
	if (!data->f_list->pipe_after && builtin_or_other_cmd(data, tmp) && !tmp->redirect)
	{	
		check_builtins_or_other_cmd(data, tmp);
		return ;
	}
	while (tmp->next)
	{
		pid[i++] = execute_commands_(data, tmp);
		tmp = tmp->next;
	}
	pid[i] = execute_last_command(data, tmp);
	close_n_wait(data->tool, pid);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}