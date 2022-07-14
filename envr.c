/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 00:07:52 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/14 21:45:28 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*before_char(char *str, int c)
{
	char			*s;
	unsigned int	i;

	s = NULL;
	i = ft_strchr1(str, c);
	s = ft_substr(str, 0, i);
	return (s);
}

void	set_env(char **envp, t_env **env)
{
	char	*name;
	char	*value;
	int		flag;
	int		i;

	*env = NULL;
	i = 0;
	while (envp[i])
	{
		name = before_char(envp[i], '=');
		value = ft_strchr(envp[i], '=') + 1;
		if (!value)
			flag = 0;
		else
			flag = 1;
		if (ft_strcmp(name, "OLDPWD"))
			add_back(env, new_node(name, value, flag));
		free(name);
		i++;
	}
}

char	*ft_getenv(t_env **env_, char *name)
{
	t_env	*env;

	env = *env_;
	while (env)
	{
		if ((env)->name && !ft_strcmp(name, (env)->name))
			return ((env)->value);
		(env) = (env)->next;
	}
	return (NULL);
}

void	env_add_change(t_env **env, char *name, char *value, int flag)
{
	t_env	*copy;

	copy = *env;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
		{
			free(copy->value);
			copy->value = value;
			copy->flag = flag;
		}
		copy = copy->next;
	}
	add_back(env, new_node(name, value, copy->flag));
}

void	env_add_change1(t_env **env, char *name, char *value, int flag)
{
	t_env	*copy;

	copy = *env;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
		{
			if (ft_strcmp(copy->value, value))
			{
				free(copy->value);
				copy->value = value;
				copy->flag = flag;
				return ;
			}
		}
		copy = copy->next;
	}
}

int	already_exists_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "OLDPWD"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	env_add_change2(t_env **env, char *name, int flag)
{
	t_env	*copy;
	char	*OLDPWD;

	copy = *env;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
		{
			if (!already_exists_oldpwd(*env))
			{
				add_back(env, new_node("OLDPWD", copy->value, copy->flag));
				return ;
			}
			else
			{
				env_add_change1(env, "OLDPWD", copy->value, flag);
				return ;
			}
		}
		copy = copy->next;
	}
}