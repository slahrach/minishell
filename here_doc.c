/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/27 20:32:22 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_redir *tmp, t_tools *tool)
{
	char	*line;
	int		len;

	if (pipe(tool->p) == -1)
		exit (1);
	line = NULL;
	len = 0;
	len = ft_strlen(tmp->content);
	while (1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		line = readline("heredoc> ");
		if (!line)
			break;
		else
			if (!ft_strncmp(line, tmp->content, len))
				break ;
		line = ft_strjoin(line, "\n");
		write(tool->p[1], line, ft_strlen(line));
		free(line);
	}
	close (tool->p[1]);
	close (tool->fd_in);
	tool->fd_in = tool->p[0];
	// read(tool->fd_in, grr, 100);
	// printf("%s", grr);
	// write (2, grr, 10);
	// write (2, "\n", 1);
	// exit (0);
}
