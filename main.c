/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/03 22:58:08 by slahrach         ###   ########.fr       */
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
}

void	handle_sigquit(int sig)
{
	if (!sig || rl_end > 0)
		exit (0);
	else
		rl_on_new_line();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*prompt;

	if (!argc || !argv)
		return (0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	set_env(envp, &data.env);
	while (1)
	{
		prompt = find_prompt();
		if (!prompt)
			prompt = "\033[1;31m$\033[0m ";
		data.line = readline (prompt);
		if (!data.line)
			exit (0);
		if (*data.line)
			add_history(data.line);
		to_parse(data.line, &data.list, data.env);
		data.f_list = devide(&data.list);
		ft_lstclear1(&data.f_list);
		free(prompt);
	}
	return (0);
}
