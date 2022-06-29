/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/28 22:54:39 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	here_doc(t_redir *tmp, t_tools *tool)
// {
// 	char	*line;
// 	int		len;

// 	if (pipe(tool->p) == -1)
// 		exit (1);
// 	line = NULL;
// 	len = 0;
// 	while (1)
// 	{
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, SIG_DFL);
// 		line = readline("heredoc> ");
// 		len = ft_strlen(line);
// 		if (!line)
// 			break;
// 		else
// 			if (!ft_strncmp(line, tmp->content, len))
// 				break ;
// 		line = ft_strjoin(line, "\n");
// 		write(tool->p[1], line, ft_strlen(line));
// 		free(line);
// 	}
// 	close (tool->p[1]);
// 	close (tool->fd_in);
// 	tool->fd_in = tool->p[0];
	// read(tool->fd_in, grr, 100);
	// printf("%s", grr);
	// write (2, grr, 10);
	// write (2, "\n", 1);
	// exit (0);
// }

void	here_doc(t_redir *tmp, t_tools *tool)
{
	int		pid;
	char	*line;
	int		len;

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
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_DFL);
			line = readline("heredoc> ");
			len = ft_strlen(line);
			if (!line)
				exit(0);
			else
				if (!ft_strncmp(line, tmp->content, len))
					exit(0);
			line = ft_strjoin(line, "\n");
			write(tool->p[1], line, ft_strlen(line));
			free(line);
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