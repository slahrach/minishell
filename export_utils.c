/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:00:14 by iouardi           #+#    #+#             */
/*   Updated: 2022/07/20 01:12:21 by iouardi          ###   ########.fr       */
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

static	int	already_exists_export_concat(char **arg, t_env *env, int flag)
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

static	char	*ft_strndup(const char *s1, int l)
{
	char	*ptr;

	ptr = (char *) malloc ((l + 1) * sizeof(char));
	if (!ptr)
		return (0);
	ft_strlcpy (ptr, s1, l + 1);
	return (ptr);
}

int	cases_concat(int flag, t_env *env, char **splited)
{
	char	*tmp;

	tmp = ft_strndup(splited[0], ft_strlen(splited[0]) - 1);
	if (parse_args_export(splited[0]) == 2)
	{
		if (!already_exists_export_concat(splited, env, flag))
			add_back(&env, new_node(tmp, splited[1], flag));
		else if (already_exists_export_concat(splited, env, flag) == 2)
			join_n_add_change(&env, splited, flag);
		free (tmp);
		return (0);
	}
	free(tmp);
	return (1);
}
