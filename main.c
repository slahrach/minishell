/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/10 20:18:21 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (rl_end > 0)
		exit (0);
	else
		return ;
}

int	main(void)
{
	char	*prompt;
	t_list	*temp;

	g_data.list = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	prompt = find_prompt();
	if (!prompt)
		prompt = "\033[1;31m$\033[0m ";
	while (1)
	{
		g_data.line = readline (prompt);
		if (!g_data.line)
			exit (0);
		if (*g_data.line)
			add_history(g_data.line);
		to_parse(g_data.line, &g_data.list);
		temp = g_data.list;
		while (temp)
		{
			printf("id = %d ------ %s\n", temp->id, temp->content);
			temp = temp->next;
		}
		free (g_data.line);
		ft_lstclear(&g_data.list);
	}
	return (0);
}
