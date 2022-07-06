/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 06:17:22 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/06 00:40:15 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_redir *tmp, t_list *tmp1, t_tools *tool, t_data *data)
{
	char	*line1;
	t_list	*tokens;
	char	*line;
	char	*delim;
	int		len;

	if (pipe(tool->p) == -1)
		exit (1);
	line1 = NULL;
	len = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = readline("heredoc> ");
		tokenize(line, data, &data->env, &tokens);
		while (tokens)
		{
			line1 = ft_strjoin(line1, tokens->content);
			//line = ft_strjoin(line, " ");
			tokens = tokens->next;
		
		}
		// printf("'%s' her len = %zu\n", tokens->content, ft_strlen(tokens->content));
		// printf("'%s' her len = %zu\n", tmp->content, ft_strlen(tmp->content));
		line = ft_strjoin(line1, "\n");
		printf("'%s'\n", line1);
		delim = ft_strjoin(tmp->content, "\n");
		// printf("%d\n", ft_strcmp(line, delim));
		if (!line)
			break;
		else if (!ft_strncmp(line, delim, len))
			break ;
		write(tool->p[1], line, ft_strlen(line));
		free(line);
	}
	close (tool->p[1]);
	tmp1->fd_in = tool->p[0];
}
