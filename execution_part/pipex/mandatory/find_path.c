/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:34:17 by iouardi           #+#    #+#             */
/*   Updated: 2022/04/06 22:57:39 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path1(char **env)
{
	int		i;
	char	*paths;
	char	**path;

	paths = NULL;
	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			paths = ft_strdup(ft_strnstr(env[i], "PATH=", 5));
			path = ft_split(paths, ':');
			break ;
		}
		i++;
	}
	free(paths);
	return (path);
}

char	*find_path2(char **path, int i)
{
	char	*path_temp1;
	int		j;

	j = 0;
	if (!access(path[i], F_OK))
	{
		while (j < i)
		{
			free(path[j]);
			j++;
		}
		j = i + 1;
		while (path[j])
		{
			free(path[j]);
			j++;
		}
		path_temp1 = path[i];
		free (path);
		return (path_temp1);
	}
	return (NULL);
}

char	*find_path(char *cmd, char **env)
{
	int		i;
	char	**path;
	char	*path_temp1;

	path = find_path1(env);
	i = 0;
	while (path[i])
	{
		path_temp1 = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free (path_temp1);
		path_temp1 = path[i];
		path[i] = ft_strjoin(path[i], cmd);
		free (path_temp1);
		if (find_path2(path, i))
			return (path[i]);
		i++;
	}
	return (NULL);
}

int	check_path(char *path)
{
	if (!access (path, F_OK))
		return (0);
	else if (ft_strchr (path, '/'))
		return (2);
	return (1);
}

void	print_error(char *cmd)
{
	char	*err;

	err = strerror (errno);
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
}
