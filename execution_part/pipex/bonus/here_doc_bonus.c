/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 23:12:59 by iouardi           #+#    #+#             */
/*   Updated: 2022/04/11 01:43:00 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_here_doc(char *argv)
{
	if (!ft_strncmp(argv, "here_doc", ft_strlen(argv)))
		return (1);
	return (0);
}

void	type_line_n_check_argv(t_pipexa piipe, char *line, char *argv, int len)
{
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, argv, len) && line[len] == '\n')
			exit(0);
		write(piipe.p[1], line, ft_strlen(line));
	}
}

void	for_my_dear_here_doc(char *argv, t_pipexa piipe)
{
	int		pid;
	char	*line;
	int		len;

	if (pipe(piipe.p) == -1)
		exit (1);
	pid = fork();
	line = NULL;
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		len = ft_strlen(argv);
		type_line_n_check_argv(piipe, line, argv, len);
		close (piipe.p[1]);
	}
	else
	{
		dup2(piipe.p[0], 0);
		close(piipe.p[0]);
		close(piipe.p[1]);
		waitpid(pid, NULL, 0);
	}
}

void	if_its_here_doc_or_not(t_pipexa piipe, char **argv, int *i, int fd1)
{
	if (check_here_doc(argv[1]))
	{
		for_my_dear_here_doc(argv[2], piipe);
		*i = 3;
	}
	else
		check_fd1(fd1, i);
}

void	free_all(char **cmd_temp1)
{
	int		i;

	i = 0;
	while (cmd_temp1[i])
	{
		free (cmd_temp1[i]);
		cmd_temp1[i] = NULL;
		i++;
	}
	free (cmd_temp1);
}
