/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/02 16:25:57 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_redir *tmp, t_list *tmp1, t_tools *tool)
{
	char	*line;
	char	*delim;
	int		len;

	if (pipe(tool->p) == -1)
		exit (1);
	line = NULL;
	len = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		line = readline("heredoc> ");
		line = ft_strjoin(line, "\n");
		delim = ft_strjoin(tmp->content, "\n");
		len = ft_strlen(line);
		if (!line)
			break;
		else
			if (!ft_strncmp(line, delim, len))
				break ;
		write(tool->p[1], line, ft_strlen(line));
		free(line);
	}
	close (tool->p[1]);
	tmp1->fd_in = tool->p[0];
}
