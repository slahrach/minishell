/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:58:32 by iouardi           #+#    #+#             */
/*   Updated: 2022/04/06 22:59:05 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd1(t_pipexa *piipe, char *argv, char **env)
{
	int		pid;
	int		fd1;

	fd1 = open(argv, O_RDONLY, 0666);
	if (fd1 < 0)
	{
		write(2, "no such file or directory\n", 27);
		return (1);
	}
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		check_path_pro(piipe);
		dup2(fd1, 0);
		dup2(piipe->p[1], 1);
		close (piipe->p[0]);
		execve(piipe->path, piipe->cmd1, env);
		print_error(piipe->cmd1[0]);
		exit (1);
	}
	return (pid);
}

int	execute_cmd2(t_pipexa *piipe, char *argv, char **env)
{
	int		pid;
	int		fd2;

	fd2 = open(argv, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		if (!piipe->path)
		{
			write(2, "command not found\n", 19);
			exit (1);
		}
		dup2(piipe->p[0], 0);
		dup2(fd2, 1);
		close (piipe->p[1]);
		execve(piipe->path, piipe->cmd2, env);
		print_error(piipe->cmd2[0]);
		return (1);
	}
	return (pid);
}
