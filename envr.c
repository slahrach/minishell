/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 00:07:52 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/19 23:54:05 by iouardi          ###   ########.fr       */
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
		if (name && copy->name && !ft_strcmp(name, copy->name))
		{
			if (value && copy->value && ft_strcmp(copy->value, value))
			{
				free(copy->value);
				copy->value = ft_strdup(value);
				copy->flag = flag;
				return ;
			}
		}
		copy = copy->next;
	}
}
