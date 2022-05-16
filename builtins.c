/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:34:44 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/16 00:07:48 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	builtins(t_list *f_list, char **env)
{
	int		atoi;
	int		i;
	char	*str_cp;
	char	pwd[256];
	t_list	*list;

	i = 0;
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
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
		return (0);
	}
	return (0);
}
