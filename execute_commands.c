/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/04 01:22:50 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipes(t_data *data, t_list **list, t_tools *tool)
{
	t_list *tmp;

	tmp = *list;

	tmp->fd_in = STDIN_FILENO;
	while (tmp->next)
	{
		if (pipe(tool->p) == -1)
			exit (1);
		tmp->fd_out = tool->p[1];
		tmp->next->fd_in = tool->p[0];
		check_redirections(data, &tmp, tool);
		tmp = tmp->next;
	}
	tmp->fd_out = STDOUT_FILENO;
	check_redirections(data, &tmp, tool);
}

void	check_redirections(t_data *data, t_list **f_list, t_tools *tool)
{
	t_redir	*tmp;
	t_list	*tmp1;

	tmp1 = (*f_list);
	tmp = tmp1->redirect;
	while (tmp)
	{
		if (tmp->id == 1)
		{
			tmp1->fd_in = open (tmp->content, O_RDONLY);
			if (tmp1->fd_in == -1)
			{
				printf("bash: %s: No such file or directory\n", tmp->content);
				g_last_exitstatus = 1;
				exit(1);
			}
		}
		if (tmp->id == 2)
			tmp1->fd_out = open (tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp->id == 5)
			tmp1->fd_out = open (tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (tmp->id == 4)
			here_doc(tmp, tmp1, tool);
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
	if (!tool->path)//in this case even if there r pipes this msg should be printed in the STDOUT
	{
		printf("bash: %s: command not found\n", tmp->arr[0]);
		tmp->exit_status = 1;
		return ;
	}
	execve(tool->path, tmp->arr, linked_list_to_table(data->env));
	tmp->exit_status = 1;
	print_error(tmp->arr[0]);
	// return ;
}

int	execute_commands_(t_data *data, t_list *tmp)
{
	int		pid;
	int		err;

	pid = fork();
	if (pid == -1)
		exit(1);
	err = 0;
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		dup2(tmp->fd_in, 0);
		close(data->tool->p[0]);
		dup2(tmp->fd_out, 1);
		check_builtins_or_other_cmd(data, tmp);
		exit(g_last_exitstatus);
	}
	else
	{
		close (tmp->fd_in);
		close (tmp->fd_out);
	}
	return (pid);
}

void	close_n_wait(t_tools *tool, int *pid, t_list *tmp)
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
	t_list	*tmp1;
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
	if (!data->f_list->pipe_after && builtin_or_other_cmd(data, tmp) && !tmp->redirect)
	{	
		check_builtins_or_other_cmd(data, tmp);
		return ;
	}
	tmp = data->f_list;
	if (tmp->err)
	{
		printf("Error\nsyntax error !\n");
		g_last_exitstatus = 258;
	}
	check_pipes(data, &data->f_list, data->tool);
	while (tmp)
	{
		pid[i++] = execute_commands_(data, tmp);
		tmp1 = tmp;
		tmp = tmp->next;
	}
	close_n_wait(data->tool, pid, tmp1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
}
