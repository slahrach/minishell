/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:51:10 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 00:51:43 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alnum_arg(char *str)
{
	if (!ft_isalnum(str[0]) && str[0] != '_')
	{
		printf("bash: unset: `%s': not a valid identifier\n", str);
		g_last_exitstatus = 258;
		return (0);
	}
	return (1);
}

int	parse_args_export(char *var)
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
		if (!check_alnum_arg(var))
			return (0);
		i++;
	}
	if (var[i] != '+' && !ft_isalnum(var[i]))
		return (0);
	else
		if (var[i] == '+')
			return (2);
	return (1);
}

int	parse_args(char *var)
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
		if (!parse_args(arr[i]))
		{
			i++;
			continue ;
		}
		unset_node(env, arr[i]);
		i++;
	}
}
