/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:13:19 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 00:54:23 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	option_is_valid_echo(char *arr)
{
	int		i;

	i = 1;
	while (arr[i])
	{
		if (arr[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_command(t_list **list)
{
	char	**arr;
	int		nl;
	int		i;

	i = 1;
	nl = 1;
	arr = (*list)->arr;
	while (arr[i] && !ft_strncmp(arr[i], "-n", 2))
	{
		if (option_is_valid_echo(arr[i]))
			break ;
		nl = 0;
		i++;
	}
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1] != 0)
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	g_last_exitstatus = 0;
}

void	pwd_command(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
		printf("%s\n", buffer);
	else
	{
		printf("pwd : command failed !\n");
		g_last_exitstatus = 1;
	}
	free (buffer);
}

int	check_path_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "PATH"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	env_command(t_list **list, t_env *env)
{
	char	**arr;
	t_env	*tmp;

	tmp = env;
	arr = (*list)->arr;
	if (!check_path_env(env))
	{
		printf ("env: No such file or directory\n");
		return ;
	}
	if (!arr[1])
	{
		while (tmp)
		{
			if (tmp->flag && tmp->name && tmp->value)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("too many arguments !\n");
		g_last_exitstatus = 127;
	}
}
