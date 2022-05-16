/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 00:07:52 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/16 00:51:09 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*before_char(char *str, int c)
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
	int		i;

	i = 0;
	while (envp[i])
	{
		name = before_char(envp[i], '=');
		value = ft_strchr(envp[i], '=') + 1;
		add_back(env, new_node(name, value));
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
	add_back(env, new_node(name, value));
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
			free(copy);
			copy = temp;
		}
		copy = copy->next;
	}
}
