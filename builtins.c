/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 20:34:44 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/14 04:20:53 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	builtins(t_list *f_list, char **env)
{
	int		i;
	char	*str_cp;
	char	pwd[256];

	i = 0;
	str_cp = ft_strmapi(f_list->inside->content, ft_tolower);
	if (!ft_strcmp(str_cp, "pwd"))
	{
		if (f_list->inside->next)
			error(3);
		if (!getcwd(pwd, sizeof (pwd)))
			error(1);
		printf("%s\n", pwd);
		return ;
	}
	if (!ft_strcmp(f_list->inside->content, "cd"))
	{
		if (chdir(f_list->inside->next->content) != 0)
			error(2);
		return ;
	}
	if (!ft_strcmp(f_list->inside->content, "exit"))
		exit(0);
	if (!ft_strcmp(str_cp, "env"))
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
