/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 05:48:33 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/06 22:57:42 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_sara/minishell.h"

void	echo_command(t_list **list)
{
	char	**arr;
	int		nl;
	int		i;

	i = 1;
	nl = 1;
	arr = (*list)->arr;
	if (arr[1] && !ft_strcmp(arr[1], "-n"))
	{
		i = 2;
		nl = 0;
	}
	while (arr[i])
	{
		printf("%s", arr[i]);
		if (arr[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
}

void	pwd_command(t_list **list)
{
	char	*buffer;

	if (ft_lstsize((*list)->inside) != 1)
	{
		printf("pwd : too many arguments !\n");
		(*list)->exit_status = 1;
		return ;
	}
	buffer = getcwd(NULL, 0);
	if (buffer)
		printf("%s\n", buffer);
	else
	{
		printf("pwd : command failed !\n");
		(*list)->exit_status = 1;
	}
}

void	env_command(t_list **list, t_env *env)
{
	char	**arr;
	t_env	*tmp;

	tmp = env;
	arr = (*list)->arr;
	if (!arr[1])
	{
		while (tmp)
		{
			if (tmp->flag)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
	else
	{
		printf("too many arguments !\n");
		(*list)->exit_status = 127;
	}
}

int	parse_args(t_list **list, char *var)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("bash: unset: `%s': not a valid identifier\n", var);
		(*list)->exit_status = 1;
		return (0);
	}
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			printf("bash: unset: `%s': not a valid identifier\n", var);
			(*list)->exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	unset_command(t_list **list, t_env *env)
{
	char	**arr;
	int		i;

	i = 1;
	arr = (*list)->arr;
	while (arr[i])
	{
		if (!parse_args(list, arr[i]))
		{
			i++;
			continue ;
		}
		unset_node(&env, arr[i]);
		i++;
	}
}
