/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/07 06:53:28 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/************will be changed based on the new struct**************/

void	check_infiles(t_redir *infile, t_tools *tool)
{
	t_redir	*tmp;

	tmp = infile;
	tool->fd_in = 0;
	while (tmp)
	{
		tool->fd_in = open (tmp, O_RDONLY);
		if (tool->fd_in == -1)
		{
			printf("bash: %s: No such file or directory\n", tmp);
			exit(1);
		}
		tmp = tmp->next;
	}
}

void	check_outfiles(t_redir *outfile, t_tools *tool)
{
	t_redir	*tmp;

	tmp = outfile;
	while (tmp->next)
	{
		tool->fd_out = open (tmp, O_WRONLY | O_CREAT, 0777);
		tmp = tmp->next;
	}
	tool->fd_out = open (tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777);
}

void	check_appends_or_outfiles(t_redir *append,t_redir *outfile, t_tools *tool)
{
	t_redir	*tmp;
	t_redir	*tmp1;

	tmp = append;
	tmp1 = outfile;
	while (tmp->next || tmp1->next)
	{
		if (tmp)
		{
			tool->fd_out = open (tmp, O_WRONLY | O_CREAT, 0777);
			tmp = tmp->next;
		}
		if (tmp1)
		{
			tool->fd_out = open (tmp1, O_WRONLY | O_CREAT, 0777);
			tmp1 = tmp->next;
		}
	}
	tool->fd_out = open (tmp, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

/************will be changed based on the new struct**************/

void	other_commands(t_data *data, t_list *tmp, t_tools *tool)
{
	if (!check_path(tmp->arr[0]) || check_path(tmp->arr[0]) == 2)
		tool->path = ft_strdup(tmp->arr[0]);
	else
		tool->path = find_path(data->env, tmp->arr[0]);
	if (!tool->path)
	{
		write(2, "command not found\n", 19);
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
	t_tools	*tool;
	int		pid;

	tool = malloc (sizeof(t_tools));
	check_infiles(tmp->infile, tool);
	if (pipe(tool->p) == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
	{
		dup2(tool->fd_in, 0);
		close (tool->fd_in);
		close(tool->p[0]);
		dup2(tool->p[1], 1);
		close(tool->p[1]);
		if (!check_builtins(tmp))
		{
			check_builtins_or_other_cmd(tmp);
			exit(0);
		}
		else
		{
			check_builtins_or_other_cmd(data, tmp);
			print_error(tmp->arr[0]);
			exit (1);
		}
	}
	else
	{
		close(tool->p[1]);
		dup2(tool->p[0], 0);
		close(tool->p[0]);
	}
	return (pid);
}

int	execute_last_commands(t_data *data, t_list *tmp)
{
	int		pid;

	
}

void	execute_commands(t_data *data)
{
	char	*str;
	t_list	*tmp;
	int		*pid;
	int		i;
	
	tmp = data->f_list;
	pid = malloc (sizeof(int) * ft_lstsize(tmp));
	while (tmp->next)
	{
		pid[i++] = execute_commands_(data, tmp);
		tmp = tmp->next;
	}
	pid[i] = execute_last_command(data, tmp);
	exit_status_command(&data);
}