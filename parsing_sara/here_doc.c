/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/09 09:47:34 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_redir *tmp, t_tools *tool)
{
	// char    *line;
	// int		pid;

	// line = NULL;
	// pid = fork();
	// tool->fd_here = open (tmp->content, O_RDWR, O_CREAT | O_TRUNC, 0666);
	// while (1)
	// {
	// 	line = ft_strjoin(line, readline(" >"));
	// 	if (line)
	// 		if (!ft_strcmp(line, tmp->content))
	// 			exit(0) ;
	// 	if (line)
	// 		ft_putstr_fd(line, tool->fd_here);
	// }
	// return (tool->fd_here);
	int		pid;
	char	*line;

	if (pipe(tool->p) == -1)
		exit (1);
	pid = fork();
	line = NULL;
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		while (1)
		{
			line = get_next_line(0);
			if (!ft_strcmp(line, tmp->content) && line[ft_strlen(tmp->content)] == '\n')
				exit(0);
			write(tool->p[1], line, ft_strlen(line));
		}
		close (tool->p[1]);
	}
	else
	{
		dup2(tool->p[0], 0);
		close(tool->p[0]);
		close(tool->p[1]);
		waitpid(pid, NULL, 0);
	}
}