/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:08:18 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/06 03:37:14 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path_1(t_env **env)
{
	t_env	*tmp;
	char	**path;

	tmp = *env;
	path = NULL;
	while (tmp)
	{
		if (ft_strnstr(tmp->name, "PATH", 4))
		{
			path = ft_split(tmp->value, ':');
			break ;
		}
		tmp = tmp->next;
	}
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

int	path_removed(t_env **env, char *cmd, char **path)
{
	if (!path)
	{
		printf("bash: %s: No such file or directory\n", cmd);
		(*env)->flag_unset_path = 1;
		return (0);
	}
	return (1);
}

char	*find_path(t_env **env, char *cmd)
{
	int		i;
	char	**path;
	char	*path_tmp;

	path = find_path_1(env);
	(*env)->flag_unset_path = 0;
	if (!path_removed(env, cmd, path))
		return (NULL);
	i = 0;
	while (path[i])
	{
		path_tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free (path_tmp);
		path_tmp = path[i];
		path[i] = ft_strjoin(path[i], cmd);
		free (path_tmp);
		if (find_path2(path, i))
			return (path[i]);
		i++;
	}
	free_all(path);
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
