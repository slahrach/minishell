/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:58:31 by iouardi           #+#    #+#             */
/*   Updated: 2022/04/10 23:15:35 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "get_next_line.h"
# include "libft/libft.h"

typedef struct s_pipexa
{
	char	*path;
	char	**cmd;
	int		p[2];
}	t_pipexa;

char	*find_path(char *cmd, char **env);
int		check_here_doc(char *argv);
void	type_line_n_check_argv(t_pipexa piipe, char *line, char *argv, int len);
void	for_my_dear_here_doc(char *argv, t_pipexa piipe);
void	if_its_here_doc_or_not(t_pipexa piipe, char **argv, int *i, int fd1);
void	execute_cmd_(t_pipexa piipe, char **env);
int		execute_cmd(t_pipexa piipe, char *argv, char **env);
void	last_command_(t_pipexa piipe, int fd, char **env, char *path_temp);
int		last_command(t_pipexa piipe, char **argv, int argc, char **env);
void	check_fd1(int fd1, int *i);
void	check_fd(int fd);
void	print_error(char *cmd);
int		check_path(char *path);
void	close_n_wait(t_pipexa piipe, int *pid);
void	if_its_here_doc_or_not(t_pipexa piipe, char **argv, int *i, int fd1);
void	free_all(char **cmd_temp1);
void	free_o_ziid_free(t_pipexa piipe);

#endif