/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:02:23 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/18 23:43:30 by iouardi          ###   ########.fr       */
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

int	already_exists_export_supp(t_env *tmp, char **arg, int flag)
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
	return (10);
}

static int	already_exists_export_concat(char **arg, t_env *env, int flag)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg[0], ft_strlen(arg[0]) - 1))
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
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, arg[0], ft_strlen(arg[0]) - 1))
		{
			tmp->value = ft_strjoin(tmp->value, arg[1]);
			return ;
		}
		tmp = tmp->next;
	}
}

static	char	*ft_strndup(const char *s1, int l)
{
	char	*ptr;

	ptr = (char *) malloc ((l + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy (ptr, s1, l + 1);
	return (ptr);
}

int	cases_concat(t_list **list, int flag, t_env *env, char **splited)
{
	char	*tmp;
	
	tmp = ft_strndup(splited[0], ft_strlen(splited[0]) - 1);
	if (parse_args_export(list, splited[0]) == 2)
	{
		if (!already_exists_export_concat(splited, env, flag))
			add_back(&env, new_node(tmp, splited[1], flag));
		else if (already_exists_export_concat(splited, env, flag) == 2)
			join_n_add_change(&env, splited, flag);
		free (tmp);
		return (0);
	}
	return (1);
}

static void	cases(t_list **list, char *arr, t_env *env)
{
	char	**splited;
	int		flag;

	flag = 1;
	if (!ft_strchr(arr, '='))
		flag = 0;
	splited = ft_split1(arr, '=');
	if (!parse_args_export(list, splited[0]))
		return ;
	if (!cases_concat(list, flag, env, splited))
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
		cases(list, arr[i], env);
		i++;
	}
}
