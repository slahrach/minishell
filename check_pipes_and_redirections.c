/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes_and_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 03:05:41 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/19 02:23:27 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_pipes(t_data *data, t_list **list, t_tools *tool)
{
	t_list *tmp;

	tmp = *list;
	tmp->fd_in = STDIN_FILENO;
	while (tmp->next)
	{
		if (pipe(tool->p) == -1)
			exit(1);
		tmp->fd_out = tool->p[1];
		tmp->next->fd_in = tool->p[0];
		if (check_redirections(data, &tmp, tool))
			return (1);
		tmp = tmp->next;
	}
	tmp->fd_out = STDOUT_FILENO;
	if (check_redirections(data, &tmp, tool))
		return (1);
	if (tmp->err)
	{
		printf("Error\nsyntax error !\n");
		g_last_exitstatus = 258;
	}
	return (0);
}

int check_redirections_supp(t_list *tmp1, t_redir *tmp)
{
	if (tmp->id == 1)
	{
		tmp1->fd_in = open(tmp->content, O_RDONLY);
		if (tmp1->fd_in == -1)
		{
			printf("bash: %s: No such file or directory\n", tmp->content);
			g_last_exitstatus = 1; // recheck this cz it didn't modify
			return (1);
		}
	}
	return (0);
}

void	handle_sigint_hrdoc(int sig)
{
	if (sig != SIGINT)
		return ;
	g_last_exitstatus = -1;
	exit(0);
}

int	ft_here_doc(t_redir *tmp, t_list *tmp1, t_tools *tool, t_data *data)
{
	pid_t	pid0;
	pid_t	pid1;
	int		p[2];

	if (pipe(tool->p) == -1)
		exit (1);
	pid0 = fork();
	if (pid0 == 0)
	{
		signal(SIGINT, handle_sigint_hrdoc);
		here_doc(tmp, tmp1, tool, data);
		exit(0);
	}
	else
		waitpid(pid0, NULL, 0);
	close (tool->p[1]);
	if (g_last_exitstatus != 130)
		tmp1->fd_in = tool->p[0];
	else
	{
		if (pipe(p) == -1)
			exit (2);
		close (p[1]);
		tmp1->fd_in = p[0];
		g_last_exitstatus = 1;
	}
	return (pid0);
}

int	how_many_heredocs_we_have(t_data *data)
{
	int		cmpt;
	t_list	*tmp;
	t_redir	*tmp1;

	cmpt = 0;
	tmp = data->f_list;
	while (tmp)
	{
		tmp1 = tmp->redirect;
		while (tmp1)
		{
			if (tmp1->id == 4)
				cmpt++;
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;
	}
	return (cmpt);
}

int	check_redirections(t_data *data, t_list **f_list, t_tools *tool)
{
	t_redir *tmp;
	t_list *tmp1;

	tmp1 = (*f_list);
	tmp = tmp1->redirect;
	if (how_many_heredocs_we_have(data) > 16)
	{
		printf("maximum here-document count exceeded\n");
		g_last_exitstatus = 2;
		exit (g_last_exitstatus);
	}
	while (tmp)
	{
		if (check_redirections_supp(tmp1, tmp))
			return (1);
		if (tmp->id == 2)
			tmp1->fd_out = open(tmp->content,
								O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (tmp->id == 5)
			tmp1->fd_out = open(tmp->content,
								O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (tmp->id == 4 && how_many_heredocs_we_have(data) <= 16)
			ft_here_doc(tmp, tmp1, tool, data);
		tmp = tmp->next;
	}
	return (0);
}

int builtin_or_other_cmd(t_data *data, t_list *tmp)
{
	char *str;

	if (tmp->arr[0])
	{
		if (data->f_list->inside->id)
			return (1);
		else if (!ft_strcmp(tmp->arr[0], "echo"))
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

void close_n_wait(t_tools *tool, int *pid)
{
	int i;

	i = 0;
	close(tool->p[0]);
	close(tool->p[1]);
	while (pid[i])
	{
		if (g_last_exitstatus == 130)
			waitpid(pid[i], NULL, 0);
		else
			{waitpid(pid[i], &g_last_exitstatus, 0);
		WIFEXITED(g_last_exitstatus);}
		i++;
	}
	g_last_exitstatus %= 255;
}
