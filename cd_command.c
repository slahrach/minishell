/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:00:33 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/14 22:00:45 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*check_path_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "HOME"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static	void	change_pwd_env(t_env **env)
{
	char	*pwd_val;

	pwd_val = getcwd(NULL, 0);
	if (pwd_val)
	{
		env_add_change2(env, "PWD", 1);
		env_add_change1(env, "PWD", pwd_val, 1);
	}
	// free (pwd_val);//
}

static	void	cd_home(t_list **list, t_env **env)
{
	char	*path;

	path = check_path_home(*env);
	if (!path)
	{
		printf("cd: HOME not set \n");
		g_last_exitstatus = 1;
		return ;
	}
	if (chdir(path))
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		g_last_exitstatus = 1;
		return ;
	}
	change_pwd_env(env);
	return ;
}

static int	success_cd(t_env **env, char *arr)
{
	t_env	*tmp_new;
	t_env	*tmp;
	t_env	*tmp1;
	char	*pwd_val;

	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "TERM_PROGRAM_VERSION"))
		{
			tmp_new = new_node("OLDPWD", arr, tmp->flag);
			tmp1 = tmp->next->next;
			tmp->next = tmp_new;
			tmp_new->next = tmp1;
			pwd_val = getcwd(NULL, 0);
			if (pwd_val)
				env_add_change1(env, "PWD", pwd_val, 1);

			// change_pwd_env(env);
			
			return (1);
		}
		tmp = tmp->next;
	}
	pwd_val = getcwd(NULL, 0);
	if (pwd_val)
		env_add_change1(env, "PWD", pwd_val, 1);
	// change_pwd_env(env);
	return (0);
}

void	cd_command(t_list **list, t_env **env)
{
	char	**arr;

	arr = (*list)->arr;
	if (!arr[1])
	{
		cd_home(list, env);
		return ;
	}
	if (!chdir(arr[1]))
	{
		if (!success_cd(env, arr[1]))
			return ;
	}
	else
	{
		printf("bash: cd: %s: No such file or directory\n", arr[1]);
		g_last_exitstatus = 1;
	}
}
