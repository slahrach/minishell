/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/11 01:56:03 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_last_exitstatus = 1;
}

void	handle_sig(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	g_last_exitstatus = 130;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*prompt;

	if (!argc || !argv || !envp)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	set_env(envp, &data.env);
	g_last_exitstatus = 0;
	while (1)
	{
		data.status = 0;
		data.error = 0;
		prompt = find_prompt(data.env);
		signal(SIGINT, handle_sigint);
		data.line = readline (prompt);
		signal(SIGINT, handle_sig);
		if (!data.line)
			break ;
		if (*data.line)
		{
			add_history(data.line);
			to_parse(data.line, &data, data.env);
			if (!data.error)
			{
				data.f_list = devide(&data, &data.list);
				if (!data.error)
					execute_commands(&data);
				ft_lstclear1(&data.f_list);
			}
			else
				ft_lstclear(&data.list);
		}
		free(prompt);
	}
	clear_env(&data.env);
	return (0);
}
