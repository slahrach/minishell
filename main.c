/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/17 22:32:38 by iouardi          ###   ########.fr       */
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

void	main_supp(t_data *data)
{
	add_history(data->line);
	tokenize(data->line, data, &data->env, &data->list_token);
	if (!data->error)
	{
		data->f_list = parse(data, &data->list_token);
		if (!data->error)
			execute_commands(data);
		ft_lstclear1(&data->f_list);
	}
	else
		ft_lstclear(&data->list_token);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*prompt;

	if (!argc || !argv)
		return (0);
	data = malloc(sizeof(t_data));
	data->env = malloc(sizeof(t_env));
	data->tool = malloc(sizeof(t_tools));
	data->tool->p[0] = -1;
	set_env(envp, &data->env);
	while (1)
	{
		data->status = 0;
		data->error = 0;
		prompt = find_prompt(data);
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline (prompt);
		signal(SIGINT, handle_sig);
		if (!data->line)
			break ;
		if (*data->line)
			main_supp(data);
		free(prompt);
	}
	clear_env(&data->env);
	free(data);
	return (0);
}
