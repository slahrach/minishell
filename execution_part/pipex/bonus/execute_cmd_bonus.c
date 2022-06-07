/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 23:10:23 by iouardi           #+#    #+#             */
/*   Updated: 2022/05/22 02:33:02 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd_(t_pipexa piipe, char **env)
{
	if (!piipe.path)
	{
		write(2, "command not found\n", 19);
		exit(1);
	}
	close(piipe.p[0]);
	dup2(piipe.p[1], 1);
	close(piipe.p[1]);
	if ()
	execve(piipe.path, piipe.cmd, env);
	free_all(piipe.cmd);
	print_error(piipe.cmd[0]);
	exit(1);
}

int	execute_cmd(t_pipexa piipe, char *argv, char **env)
{
	int		pid;
	char	**cmd_temp1;

	if (pipe(piipe.p) == -1)
		exit (1);
	pid = fork();
	if (pid == -1)
		exit (1);
	piipe.cmd = ft_split(argv, ' ');
	cmd_temp1 = piipe.cmd;
	if (!check_path(piipe.cmd[0]) || check_path(piipe.cmd[0]) == 2)
		piipe.path = ft_strdup(piipe.cmd[0]);
	else
		piipe.path = find_path (piipe.cmd[0], env);
	if (pid == 0)
		execute_cmd_(piipe, env);
	else
	{
		free(piipe.path);
		free_all(cmd_temp1);
		close(piipe.p[1]);
		dup2(piipe.p[0], 0);
		close(piipe.p[0]);
	}
	return (pid);
}

void	last_command_(t_pipexa piipe, int fd, char **env, char *path_temp)
{
	dup2(fd, 1);
	execve(piipe.path, piipe.cmd, env);
	print_error(piipe.cmd[0]);
	free(path_temp);
}

int	last_command(t_pipexa piipe, char **argv, int argc, char **env)
{
	int		fd;
	char	*path_temp;
	int		pid;

	piipe.cmd = ft_split(argv[argc - 2], ' ');
	fd = 0;
	path_temp = piipe.cmd[0];
	if (!check_path(piipe.cmd[0]) || check_path(piipe.cmd[0]) == 2)
		piipe.path = ft_strdup(piipe.cmd[0]);
	else
		piipe.path = find_path (piipe.cmd[0], env);
	if (check_here_doc(argv[1]))
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	check_fd(fd);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
		return (last_command_(piipe, fd, env, piipe.path), pid);
	else
		return (free_o_ziid_free(piipe), pid);
}

void	check_fd1(int fd1, int *i)
{
	if (fd1 < 0)
	{
		*i = 3;
		write(2, "shell: no such file or directory\n", 34);
	}
	dup2(fd1, 0);
}
