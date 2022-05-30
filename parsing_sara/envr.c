/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 00:07:52 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/30 17:10:11 by iouardi          ###   ########.fr       */
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
		if (!ft_strchr(envp[i], '='))
			flag = 0;
		else
			flag = 1;
		if (ft_strcmp(name, "OLDPWD"))
			add_back(env, new_node(name, value, flag));
		i++;
	}
}

char	*ft_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	env_add_change(t_env **env, char *name, char *value)
{
	t_env	*copy;

	copy = *env;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
		{
			free(copy->value);
			copy->value = value;
		}
		copy = copy->next;
	}
	add_back(env, new_node(name, value, copy->flag));//new
}

void	env_add_change1(t_env **env, char *name, char *value)
{
	t_env	*copy;

	copy = *env;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
		{
			free(copy->value);
			copy->value = value;
		}
		copy = copy->next;
	}
}

void	unset_node(t_env **env, char *name)
{
	t_env	*temp;
	t_env	*copy;

	copy = *env;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
		{
			temp = copy->next;
			free(copy->name);
			free(copy->value);
			// free(copy->flag);//new
			free(copy);
			copy = temp;
		}
		copy = copy->next;
	}
}
