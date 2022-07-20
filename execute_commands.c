/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:35:03 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 23:31:22 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands_supp_supp(t_list *tmp)
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
		execute_commands_supp_supp(tmp);
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
	{
		free (pid);
		return (1);
	}
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
	{
		free (pid);
		return ;
	}
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
