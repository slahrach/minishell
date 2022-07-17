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
	char	**splited;
	char	*line;
	int		i;
	int		j;

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
		write(tool->p[1], "\n", 1);
	}
}
