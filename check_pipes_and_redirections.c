/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipes_and_redirections.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 03:05:41 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 22:59:01 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes_supp(t_data *data, t_list *tmp, t_tools *tool)
{
	if (pipe(tool->p) == -1)
	{
		printf("pipe failed\n");
		return (2);
	}
	tmp->fd_out = tool->p[1];
	tmp->next->fd_in = tool->p[0];
	ft_lstadd_back_fds(&data->fd, new_fds(tmp->next->fd_in));
	ft_lstadd_back_fds(&data->fd, new_fds(tmp->fd_out));
	if (check_redirections(data, &tmp, tool))
		return (1);
	return (0);
}

int	check_pipes(t_data *data, t_list **list, t_tools *tool)
{
	t_list	*tmp;

	tmp = *list;
	tmp->fd_in = STDIN_FILENO;
	while (tmp->next)
	{
		if (check_pipes_supp(data, tmp, tool))
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

int	check_redir_supp(t_data *data, t_list *tmp1, t_redir *tmp, t_tools *tool)
{
	if (tmp->id == 1)
	{
		tmp1->fd_in = open(tmp->content, O_RDONLY);
		ft_lstadd_back_fds(&data->fd, new_fds(tmp1->fd_in));
		if (tmp1->fd_in == -1)
		{
			printf("bash: %s: No such file or directory\n", tmp->content);
			g_last_exitstatus = 1;
			return (1);
		}
	}
	else if (tmp->id == 4 && how_many_heredocs_we_have(data) <= 16)
	{
		if (ft_here_doc(tmp, tmp1, tool, data))
			return (1);
	}
	return (0);
}

int	check_redirections(t_data *data, t_list **f_list, t_tools *tool)
{
	t_redir	*tmp;
	t_list	*tmp1;

	tmp1 = (*f_list);
	tmp = tmp1->redirect;
	check_herdocs_num(data);
	while (tmp)
	{
		if (check_redir_supp(data, tmp1, tmp, tool))
			return (1);
		if (tmp->id == 2)
		{
			tmp1->fd_out = open(tmp->content, \
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
			ft_lstadd_back_fds(&data->fd, new_fds(tmp1->fd_out));
		}
		if (tmp->id == 5)
		{
			tmp1->fd_out = open(tmp->content, \
				O_WRONLY | O_CREAT | O_APPEND, 0777);
			ft_lstadd_back_fds(&data->fd, new_fds(tmp1->fd_out));
		}
		tmp = tmp->next;
	}
	return (0);
}

void	close_n_wait(t_tools *tool, int *pid)
{
	int	i;

	i = 0;
	close(tool->p[0]);
	close(tool->p[1]);
	while (pid[i])
	{
		waitpid(pid[i], &g_last_exitstatus, 0);
		WIFEXITED(g_last_exitstatus);
		if (WIFSIGNALED(g_last_exitstatus))
			g_last_exitstatus = WTERMSIG(g_last_exitstatus) + 128;
		i++;
	}
	g_last_exitstatus %= 255;
}
