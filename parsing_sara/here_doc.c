/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/08 08:59:11 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    here_doc(t_redir *tmp, t_tools *tool)
{
	char    *line;
	int		pid;

	line = NULL;
	pid = fork();
	tool->fd_here = open (tmp->content, O_RDWR, O_CREAT | O_TRUNC, 0666);
	while (1)
	{
		line = ft_strjoin(line, readline("heredoc> "));
		if (line)
			if (!ft_strcmp(line, tmp->content))
				exit(0) ;
		if (line)
			ft_putstr_fd(line, tool->fd_here);
	}
	return (tool->fd_here);
}