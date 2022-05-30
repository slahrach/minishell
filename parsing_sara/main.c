/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:24:31 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/26 17:29:07 by iouardi          ###   ########.fr       */
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
	prompt = find_prompt();
	if (!prompt)
		prompt = "\033[1;31m$\033[0m ";
	set_env(envp, &data.env);
	while (1)
	{
		data.line = readline (prompt);
		if (!data.line)
			exit (0);
		if (*data.line)
			add_history(data.line);
		to_parse(data.line, &data.list, data.env);
		data.f_list = devide(&data.list);
		execute_commands(&data);
		// t_list *tmp = data.f_list;
		// t_env *tmp ;
		// while (tmp)
		// {
			// printf("content = %s \n", tmp->content);
			// // printf("inside = %s \n", tmp->inside);
			// printf("id = %d \n", tmp->id);
			// printf("pipe_after = %d \n", tmp->pipe_after);
			// printf("pipe_before = %d \n", tmp->pipe_before);
			// printf("infile = %s \n", tmp->infile);
			// printf("output = %s \n", tmp->output);
			// printf("append = %s \n", tmp->append);
			// printf("delimiter = %s \n", tmp->delimiter);
		// 	int i = 0;
		// 	while (tmp->arr[i])
		// 	{
		// 		printf("arr[%d] = %s}\n", i, tmp->arr[i]);
		// 		i++;
		// 	}
		// 	puts(" ");
		// 	tmp = tmp->next;
		// }
		//while (1);
		ft_lstclear1(&data.f_list);
	}
	return (0);
}
