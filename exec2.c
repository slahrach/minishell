/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 23:13:19 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/19 00:33:24 by iouardi          ###   ########.fr       */
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
		if (!*arr[i])
			printf("DONE\n");
		printf("'%s'", arr[i]);
		if (arr[i + 1] != 0)
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	g_last_exitstatus = 0;
}

void	pwd_command(t_list **list)
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

void	env_command(t_list **list, t_env *env)
{
	char	**arr;
	t_env	*tmp;

	tmp = env;
	arr = (*list)->arr;
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

int	parse_args_export(t_list **list, char *var)
{
	int		i;
	int		l;

	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("bash: unset: `%s': not a valid identifier\n", var);
		g_last_exitstatus = 258;
		return (0);
	}
	i = 1;
	l = ft_strlen(var) - 1;
	while (i < l)
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			printf("bash: unset: `%s': not a valid identifier\n", var);
			g_last_exitstatus = 258;
			return (0);
		}
		i++;
	}
	if (var[i] != '+' && !ft_isalnum(var[i]))
		return (0);
	else
		if (var[i] == '+')
			return (2);
	return (1);
}

int	parse_args(t_list **list, char *var)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("bash: unset: `%s': not a valid identifier\n", var);
		g_last_exitstatus = 258;
		return (0);
	}
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			printf("bash: unset: `%s': not a valid identifier\n", var);
			g_last_exitstatus = 258;
			return (0);
		}
		i++;
	}
	return (1);
}

int	already_exists_unset(char *arr, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(arr, tmp->name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	unset_command(t_list **list, t_env **env)
{
	char	**arr;
	int		i;

	i = 1;
	arr = (*list)->arr;
	while (arr[i])
	{
		if (!already_exists_unset(arr[i], *env))
		{
			i++;
			continue ;
		}
		if (!parse_args(list, arr[i]))
		{
			i++;
			continue ;
		}
		unset_node(env, arr[i]);
		i++;
	}
}
