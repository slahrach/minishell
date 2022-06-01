/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:58:31 by iouardi           #+#    #+#             */
/*   Updated: 2022/04/06 23:03:25 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include "libft/libft.h"

typedef struct s_pipexa
{
	char	*path;
	char	**cmd1;
	char	**cmd2;
	int		p[2];
}	t_pipexa;

char	*find_path(char *cmd, char **env);
int		execute_cmd2(t_pipexa *piipe, char *argv, char **env);
int		execute_cmd1(t_pipexa *piipe, char *argv, char **env);
void	check_path_pro(t_pipexa *piipe);
void	close_n_wait(t_pipexa *piipe, int pid1, int pid2);
void	check_path_pro_max(t_pipexa *piipe, char **env, char *cmd);
void	print_error(char *cmd);
int		check_path(char *path);

#endif