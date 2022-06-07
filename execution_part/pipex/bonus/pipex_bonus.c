/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:58:01 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/01 01:19:59 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_n_wait(t_pipexa piipe, int *pid)
{
	int		i;

	i = 0;
	close(piipe.p[0]);
	close(piipe.p[1]);
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	check_fd(int fd)
{
	if (fd == -1)
	{
		write(2, "no such file or directory\n", 27);
		exit(1);
	}
}

void	free_o_ziid_free(t_pipexa piipe)
{
	free(piipe.path);
	free_all(piipe.cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_pipexa	piipe;
	int			i;
	int			j;
	int			*pid;
	int			fd1;

	i = 2;
	j = 0;
	pid = malloc((argc - 3) * sizeof(int));
	fd1 = open (argv[1], O_RDONLY, 0666);
	piipe.path = NULL;
	if (argc >= 5)
	{
		// if_its_here_doc_or_not(piipe, argv, &i, fd1);
		while (i < argc - 2)
			pid[j++] = execute_cmd(piipe, argv[i++], env);
		pid[j] = last_command(piipe, argv, argc, env);
		free(piipe.cmd);
		close_n_wait(piipe, pid);
	}
	else
		write(2, "please insert at least two commands\n", 37);
}
