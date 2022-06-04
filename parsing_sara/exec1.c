/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:47:11 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/03 22:44:57 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_sara/minishell.h"

char	*check_path_home(t_env *env)
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

void	change_pwd_env(t_env *env)
{
	char	*pwd_val;

	pwd_val = getcwd(NULL, 0);
	if (pwd_val)
		env_add_change1(&env, "PWD", pwd_val, 1);
}

void	cd_command(t_list **list, t_env *env)
{
	char	**arr;
	int		i;
	t_env	*tmp_new;
	t_env	*tmp;
	t_env	*tmp1;
	char	*path;

	arr = (*list)->arr;
	i = 1;
	tmp = env;
	if (!arr[1])
	{
		path = check_path_home(env);
		if (!path)
		{
			printf("cd: HOME not set \n");
			(*list)->exit_status = 1;
			return ;
		}
		chdir(path);
		change_pwd_env(env);
		return ;
	}
	tmp = env;
	if (!chdir(arr[1]))
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, "TERM_PROGRAM_VERSION"))
			{
				tmp_new = new_node("OLDPWD", arr[1], tmp->flag);
				tmp1 = tmp->next->next;
				tmp->next = tmp_new;
				tmp_new->next = tmp1;
				change_pwd_env(env);
				return ;
			}
			tmp = tmp->next;
		}
		change_pwd_env(env);
	}
	else
	{
		printf("bash: cd: %s: No such file or directory\n", arr[1]);
		(*list)->exit_status = 1;
	}
}

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

char	**split_name_value(char	*arg)
{
	char	**arr;

	arr = ft_split(arg, '=');
	return (arr);
}

int	already_exists_export(char **arg, t_env *env, int flag)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, arg[0]))
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
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_command(t_list **list, t_env *env)
{
	char	**arr;
	int		i;
	char	**arg_splited;
	int		flag;

	i = 1;
	arr = (*list)->arr;
	if (!arr[1] || !(*arr[1]))
	{
		print_export_env(env);
		return ;
	}
	while (arr[i])
	{
		if (*arr[i] == '=')
		{
			printf("export: `=': not a valid identifier");
			(*list)->exit_status = 1;
			return ;
		}
		if (!ft_strchr(arr[i], '='))
			flag = 0;
		else
			flag = 1;
		arg_splited = split_name_value(arr[i]);
		if (!parse_args(list, arg_splited[0]))
		{
			i++;
			continue ;
		}
		if (!already_exists_export(arg_splited, env, flag))
			add_back(&env, new_node(arg_splited[0], arg_splited[1], flag));
		else if (already_exists_export(arg_splited, env, flag) == 2)
			env_add_change1(&env, arg_splited[0], arg_splited[1], flag);
		else if (already_exists_export(arg_splited, env, flag) == 3)
			env_add_change1(&env, arg_splited[0], ft_strdup(""), flag);
		i++;
	}
}

void	exit_command(t_list **f_list)
{
	char	**arr;
	int		atoi;
	t_list	*list;

	list = (*f_list)->inside;
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	arr = (*f_list)->arr;
	if (ft_lstsize(list) > 1)
	{
		printf("%s\n", arr[1]);
		atoi = ft_atoi(list->next->content);
		printf("atoi = %d\n", atoi);
		if (!atoi && ft_strcmp(list->next->content, "0"))
		{
			write (2, "numeric argument required !\n", 28);
			(*f_list)->exit_status = 255;
		}
		else if (ft_lstsize(list) > 2)
		{
			write (2, "too many arguments \n", 21);
			(*f_list)->exit_status = 1;
		}
		else
			(*f_list)->exit_status = atoi % 256;
	}
	printf("exit\n");
	printf("%d\n", (*f_list)->exit_status);
	//exit(0);
}

void	execute_commands(t_data	*data)
{
	if (!ft_strcmp(data->f_list->arr[0], "echo"))
		echo_command(&data->f_list);
	else if (!ft_strcmp(data->f_list->arr[0], "cd"))
		cd_command(&data->f_list, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "pwd"))
		pwd_command(&data->f_list);
	else if (!strcmp(data->f_list->arr[0], "export"))
		export_command(&data->f_list, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "env"))
		env_command(&data->f_list, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "unset"))
		unset_command(&data->f_list, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "exit"))
		exit_command(&data->f_list);
}
