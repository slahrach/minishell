/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/14 04:54:46 by slahrach         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_data	data;
	char	*prompt;
	t_list	*temp;
	t_list	*tempi;

	if (!argc || !argv || !env)
		return (0);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	prompt = find_prompt();
	if (!prompt)
		prompt = "\033[1;31m$\033[0m ";
	while (1)
	{
		i = 1;
		data.line = readline (prompt);
		if (!data.line)
			exit (0);
		if (*data.line)
			add_history(data.line);
		to_parse(data.line, &data.list);
		data.f_list = devide(data.list);
		ft_lstclear(&data.list);
		temp = data.f_list;
		//this while is just for test to see result
		while (temp)
		{
			printf("infile == %s\n", temp->infile);
			printf("output == %s\n", temp->output);
			printf("delimiter == %s\n", temp->delimiter);
			printf("append == %s\n", temp->append);
			printf("pipe after == %d\n", temp->pipe_after);
			printf("pipe before == %d\n", temp->pipe_before);
			tempi = temp->inside;
			while (tempi)
			{
				printf("%s*****", tempi->content);
				tempi = tempi->next;
			}
			printf("\ncommand : %d\n", i);
			temp = temp->next;
			i++;
		}
		ft_lstclear1(&data.f_list);
	}
	return (0);
}
