/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:02:23 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/20 01:10:33 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	already_exists_export(char **arg, t_env *env, int flag)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, arg[0]))
		{
			if (already_exists_export_supp(tmp, arg, flag) == 1)
				return (1);
			if (already_exists_export_supp(tmp, arg, flag) == 2)
				return (2);
			if (already_exists_export_supp(tmp, arg, flag) == 3)
				return (3);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	join_n_add_change(t_env **env, char **arg, int flag)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg[0], ft_strlen(arg[0]) - 1))
		{
			tmp->value = ft_strjoin(tmp->value, arg[1]);
			printf ("%d=flag\n", flag);
			tmp->flag = flag;
			return ;
		}
		tmp = tmp->next;
	}
}

static void	cases(char *arr, t_env *env)
{
	char	**splited;
	int		flag;

	flag = 1;
	if (!ft_strchr(arr, '='))
		flag = 0;
	splited = ft_split1(arr, '=');
	if (!parse_args_export(splited[0]))
	{
		free_all(splited);
		return ;
	}
	if (!cases_concat(flag, env, splited))
	{
		free_all(splited);
		return ;
	}
	if (!already_exists_export(splited, env, flag))
		add_back(&env, new_node(splited[0], splited[1], flag));
	else if (already_exists_export(splited, env, flag) == 2)
		env_add_change1(&env, splited[0], splited[1], flag);
	else if (already_exists_export(splited, env, flag) == 3)
		env_add_change1(&env, splited[0], ft_strdup(""), flag);
	free_all(splited);
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
			g_last_exitstatus = 1;
			return ;
		}
		cases(arr[i], env);
		i++;
	}
}
