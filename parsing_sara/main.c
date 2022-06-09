/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/09 09:56:08 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)//needs protection inside the child process
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sig(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
}

int	main(int argc, char **argv, char **envp)
{
	// t_list	*inside;
	t_data	data;
	char	*prompt;

	if (!argc || !argv || !envp)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	set_env(envp, &data.env);
	while (1)
	{
		prompt = find_prompt(data.env);
		if (!prompt)
			prompt = ft_strdup("\033[1;31m$\033[0m ");
		signal(SIGINT, handle_sigint);
		data.line = readline (prompt);
		signal(SIGINT, handle_sig);
		if (!data.line)
			exit (0);
		if (*data.line)
		{
			add_history(data.line);
			to_parse(data.line, &data.list, data.env);
			data.f_list = devide(&data.list);
			execute_commands(&data);
		}
		free(prompt);
		ft_lstclear1(&data.f_list);
	}
	return (0);
}
