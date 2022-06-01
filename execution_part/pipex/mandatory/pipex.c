/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:58:01 by iouardi           #+#    #+#             */
/*   Updated: 2022/04/10 21:50:24 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_path_pro(t_pipexa *piipe)
{
	if (!piipe->path)
	{
		write(2, "command not found\n", 19);
		exit (1);
	}
}

void	close_n_wait(t_pipexa *piipe, int pid1, int pid2)
{
	close(piipe->p[0]);
	close(piipe->p[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	check_path_pro_max(t_pipexa *piipe, char **env, char *cmd)
{
	if (!check_path(cmd) || check_path(cmd) == 2)
		piipe->path = ft_strdup(cmd);
	else
		piipe->path = find_path (cmd, env);
}

int	main(int argc, char **argv, char **env)
{
	t_pipexa	*piipe;
	int			pid1;
	int			pid2;

	if (argc == 5)
	{
		piipe = malloc(sizeof(t_pipexa));
		piipe->cmd1 = ft_split(argv[2], ' ');
		piipe->cmd2 = ft_split(argv[3], ' ');
		check_path_pro_max(piipe, env, piipe->cmd1[0]);
		if (pipe(piipe->p) == -1)
			exit(1);
		pid1 = execute_cmd1(piipe, argv[1], env);
		free(piipe->path);
		if (pid1 == 2)
			exit(1);
		check_path_pro_max(piipe, env, piipe->cmd2[0]);
		pid2 = execute_cmd2(piipe, argv[4], env);
		if (pid2 == 2)
			exit(1);
		close_n_wait(piipe, pid1, pid2);
	}
	else
		write(2, "please insert two commmands\n", 29);
}
