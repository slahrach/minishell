/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:34:44 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/16 23:21:16 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	builtins(t_list *f_list, t_env **env)
{
	t_env	*copy;
	int		atoi;
	int		i;
	char	*str_cp;
	char	*name;
	char	*value;
	char	pwd[256];
	t_list	*list;

	i = 0;
	copy = *env;
	list = f_list->inside;
	str_cp = ft_strmapi(list->content, ft_tolower);
	if (!ft_strcmp(str_cp, "pwd"))
	{
		if (!getcwd(pwd, sizeof (pwd)))
		{
			write(2, "commande failed !", 18);
			return (1);
		}
		printf("%s\n", pwd);
		return (0);
	}
	if (!ft_strcmp(list->content, "cd"))
	{
		if (!list->next)
		{
			if (chdir(getenv("HOME")) != 0)
			{
				write(2, "HOME not set\n", 13);
				return (1);
			}
		}
		if (chdir(list->next->content) != 0)
		{
			write (2, "changing directory failed ! ", 2);
			error(2);
		}
		return (0);
	}
	if (!ft_strcmp(list->content, "exit"))
	{
		if (ft_lstsize(list) > 2)
		{
			write (2, "too many arguments \n", 21);
			return (1);
		}
		if (ft_lstsize(list) == 2)
		{
			atoi = ft_atoi(list->next->content);
			if (!atoi && ft_strcmp(list->next->content, "0"))
			{
				write (2, "numeric argument is required !", 31);
				return (255);
			}
			else
			{
				printf("exit\n");
				return (atoi % 256);
			}
		}
		printf("exit\n");
		return (0);
		//exit(0);
	}
	if (!ft_strcmp(str_cp, "env"))
	{
		if (list->next)
		{
			write (2, "too many arguments \n", 21);
			return (127);
		}
		while (copy)
		{
			printf("%s=%s\n", copy->name, copy->value);
			copy = copy->next;
		}
		return (0);
	}
	if (!ft_strcmp(list->content, "unset"))
	{
		if (list->next)
			unset_node(env, list->next->content);
		return (0);
	}
	if (!ft_strcmp(f_list->arr[0], "export"))
	{
		i = 1;
		while (f_list->arr[i])
		{
			if (!ft_strcmp(f_list->arr[i], "="))
			{
				if (i - 1 > 0)
					name = f_list->arr[i - 1];
				if (f_list->arr[i + 1])
					value = f_list->arr[i + 1];
				else
					value = ft_strdup("");
				if (name && value)
					env_add_change(env, name, value);
			}
		}
	}
	return (0);
}
