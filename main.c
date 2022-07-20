/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/20 05:11:07 by slahrach         ###   ########.fr       */
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
	t_fds	*tmp;

	tmp = data->fd;
	add_history(data->line);
	tokenize(data->line, data, &data->env, &data->list_token);
	if (!data->error)
	{
		data->f_list = parse(data, &data->list_token);
		if (!data->error)
		{	
			execute_commands(data);
			while (tmp)
			{
				close (tmp->fd);
				tmp = tmp->next;
			}
			clear_fds(&data->fd);
		}
		ft_lstclear1(&data->f_list);
	}
	ft_lstclear(&data->list_token);
}

static int	init(t_data *data)
{
	data->signal_flag = 1;
	data->status = 0;
	data->error = 0;
	data->fd = NULL;
	data->prompt = find_prompt(data);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	data->line = readline (data->prompt);
	signal(SIGINT, handle_sig);
	if (!data->line)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (!argc || !argv)
		return (0);
	data = malloc(sizeof(t_data));
	data->tool = malloc(sizeof(t_tools));
	data->tool->p[0] = -1;
	set_env(envp, &data->env);
	while (1)
	{
		if (init(data))
			break ;
		if (*data->line)
			main_supp(data);
		free(data->prompt);
		free(data->line);
	}
	clear_env(&data->env);
	free(data->tool);
	free(data);
	return (0);
}
