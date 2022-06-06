/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/07 00:45:55 by slahrach         ###   ########.fr       */
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
	//t_list	*inside;
	t_data	data;
	char	*prompt;

	if (!argc || !argv || !envp)
		return (0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	set_env(envp, &data.env);
	while (1)
	{
		prompt = find_prompt(data.env);
		if (!prompt)
			prompt = ft_strdup("\033[1;31m$\033[0m ");
		data.line = readline (prompt);
		if (!data.line)
			exit (0);
		if (*data.line)
		{
			add_history(data.line);
			to_parse(data.line, &data.list, data.env);
			data.f_list = devide(&data.list);
			execute_commands(&data);
		}
		//t_list *tmp = data.f_list;
		/*while (tmp)
		{
			printf("pipe_after = %d \n", tmp->pipe_after);
			printf("pipe_before = %d \n", tmp->pipe_before);
			while (tmp->append)
			{
				printf("***append****%s\n", tmp->append->content);
				tmp->append = tmp->append->next;
			}
			while (tmp->infile)
			{
				printf("***infile****%s\n", tmp->infile->content);
				tmp->infile = tmp->infile->next;
			}
			while (tmp->outfile)
			{
				printf("***outfile****%s\n", tmp->outfile->content);
				tmp->outfile = tmp->outfile->next;
			}
			while (tmp->delimiter)
			{
				printf("***delimiter****%s\n", tmp->delimiter->content);
				tmp->delimiter = tmp->delimiter->next;
			}
			inside = tmp->inside;
			while (inside)
			{
				printf("%s\n", inside->content);
				inside = inside->next;
			}
			tmp = tmp->next;
		}
		//while (1);*/
		free(prompt);
		ft_lstclear1(&data.f_list);
	}
	return (0);
}
