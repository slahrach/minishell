/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 05:23:01 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_supp(char **splited, char *line, t_tools *tool)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (splited[i])
	{
		while (line[j] && line[j] == ' ')
		{
			write(tool->p[1], " ", 1);
			j++;
		}
		write(tool->p[1], splited[i], ft_strlen(splited[i]));
		while (line[j] && line[j] != ' ')
			j++;
		i++;
	}
}

void	here_doc(t_redir *tmp, t_tools *tool, t_data *data)
{
	char	**splited;
	char	*line;
	int		i;

	while (1)
	{
		i = 0;
		signal(SIGQUIT, SIG_IGN);
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, tmp->content))
			break ;
		splited = ft_split(line, ' ');
		while (splited[i])
		{
			splited[i] = expansion(data, splited[i], &data->env);
			i++;
		}
		here_doc_supp(splited, line, tool);
		write(tool->p[1], "\n", 1);
		free_all(splited);
		free (line);
	}
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

void	check_herdocs_num(t_data *data)
{
	if (how_many_heredocs_we_have(data) > 16)
	{
		printf("maximum here-document count exceeded\n");
		g_last_exitstatus = 2;
		exit (g_last_exitstatus);
	}
}

int	ft_here_doc(t_redir *tmp, t_list *tmp1, t_tools *tool, t_data *data)
{
	pid_t	pid0;

	if (pipe(tool->p) == -1)
	{
		printf("pipe failed\n");
		g_last_exitstatus = 1;
		return (1);
	}
	pid0 = fork();
	if (pid0 == -1)
	{
		printf("fork failed\n");
		g_last_exitstatus = 1;
		return (1);
	}
	if (pid0 == 0)
	{
		signal(SIGINT, SIG_DFL);
		here_doc(tmp, tool, data);
		exit(0);
	}
	else
		waitpid(pid0, NULL, 0);
	close (tool->p[1]);
	if (g_last_exitstatus != 130)
	{
		tmp1->fd_in = tool->p[0];
		ft_lstadd_back_fds(&data->fd, new_fds(tmp1->fd_in));
	}
	else
	{
		data->signal_flag = 0;
		g_last_exitstatus = 1;
	}
	return (0);
}
