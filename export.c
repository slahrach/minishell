/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:02:23 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/06 22:14:31 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!tmp->value && tmp->flag)
			printf("declare -x %s=\"\"\n", tmp->name);
		else if (!tmp->value && !tmp->flag)
			printf("declare -x %s\n", tmp->name);
		else
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

static int	already_exists_export(char **arg, t_env *env, int flag)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, arg[0]))
		{
			if ((tmp->value && arg[1]))
			{
				if (!ft_strcmp(tmp->value, arg[1]))
					return (1);
				else
					return (2);
			}
			else if (!tmp->value && arg[1])
				return (2);
			else if ((!arg[1] && flag))
				return (3);
			else if (!arg[1] && !tmp->value && !flag)
				return (1);
			else if (!arg[1] && tmp->value && !flag)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	cases(t_list **list, char *arr, t_env *env)
{
	char	**splited;
	int		flag;

	flag = 1;
	if (!ft_strchr(arr, '='))
		flag = 0;
	splited = ft_split(arr, '=');
	if (!parse_args(list, splited[0]))
		return ;
	if (!already_exists_export(splited, env, flag))
		add_back(&env, new_node(splited[0], splited[1], flag));
	else if (already_exists_export(splited, env, flag) == 2)
		env_add_change1(&env, splited[0], splited[1], flag);
	else if (already_exists_export(splited, env, flag) == 3)
		env_add_change1(&env, splited[0], ft_strdup(""), flag);
}

void	export_command(t_list **list, t_env *env)
{
	char	**arr;
	int		i;

	i = 1;
	arr = (*list)->arr;
	if (!arr[1] || !(*arr[1]))
	{
		print_export_env(env);
		return ;
	}
	while (arr[i])
	{
		if (*arr[i] == '=')
		{
			printf("export: `=': bad assigment\n");
			(*list)->exit_status = 1;
			return ;
		}
		cases(list, arr[i], env);
		i++;
	}
}