/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:08:18 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/10 23:37:32 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path_1(t_env *env)
{
	t_env	*tmp;
	char	**path;

	tmp = env;
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

void	free_all(char **cmd_temp1)//recheck this cz it may cz a prblm
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

char	*find_path(t_env *env, char	*cmd)
{
	int		i;
	char	**path;
	char	*path_tmp;

	path = find_path_1(env);
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
