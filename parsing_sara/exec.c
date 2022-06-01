/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:47:11 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/01 01:07:50 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_sara/minishell.h"

void    echo_command(char **arr)
{
	int		i;

	if (!ft_strncmp(arr[1], "-n", ft_strlen(arr[1])))
	{
		i = 2;
		while (arr[i])
		{
			write (1, arr[i], ft_strlen(arr[i]));
			i++;
		}
	}
	else
	{
		i = 1;
		while (arr[i])
		{
			write (1, arr[i], ft_strlen(arr[i]));
			i++;
		}
		write (1, "\n", 1);
	}
}

char	*check_path_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strnstr(tmp->name, "HOME", ft_strlen(tmp->name)))
			return(tmp->value);
		tmp= tmp->next;
	}
	return (NULL);
}

void	cd_command(char	**arr, t_env *env)
{
	int		i;
	t_env	*tmp_new;
	t_env	*tmp;
	t_env	*tmp1;
	char	*path;

	i = 1;
	tmp = env;
	if (!arr[1])
	{
		path = check_path_home(env);
		chdir(path);
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
				return ;
			}
			tmp = tmp->next;
		}
	}
	else
		printf("bash: cd: %s: No such file or directory\n", arr[1]);
}

void	pwd_command()
{
	char	*buffer;

	if ((buffer = getcwd(NULL, 0)))
		printf("%s\n", buffer);//don't forget to check in case of an error
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

int	parse_args(char *var)
{
	int		i;

	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("bash: export: `%s': not a valid identifier\n", var);
		return (0);
	}
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			printf("bash: export: `%s': not a valid identifier\n", var);
			return (0);
		}
		i++;
	}
	return (1);
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

void	export_command(char **arr, t_env *env)
{
	int		i;
	char	**arg_splited;
	int		flag;

	i = 1;
	if (!arr[1])
	{
		print_export_env(env);
		return ;
	}
	while (arr[i])
	{
		if (!ft_strchr(arr[i], '='))
			flag = 0;
		else
			flag = 1;
		arg_splited = split_name_value(arr[i]);
		if (!parse_args(arg_splited[0]))
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

void	env_command(char **arr, t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = env;
	if (!arr[1])
	{
		while (tmp)
		{
			if (tmp->flag)
				printf("%s=%s\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
}

void	unset_command(char **arr, t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 1;
	while (arr[i])
	{
		if (!parse_args(arr[i]))
		{
			i++;
			continue ;
		}
		printf("arg = %s\n", arr[i]);
		unset_node(&env, arr[i]);
		i++;
	}
}

void	execute_commands(t_data	*data)
{
	if (!ft_strcmp(data->f_list->arr[0], "echo"))
		echo_command(data->f_list->arr);
	else if (!ft_strcmp(data->f_list->arr[0], "cd"))
		cd_command(data->f_list->arr, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "pwd"))
		pwd_command();
	else if (!ft_strcmp(data->f_list->arr[0], "export"))
		export_command(data->f_list->arr, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "env"))
		env_command(data->f_list->arr, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "unset"))
		unset_command(data->f_list->arr, data->env);
	else if (!ft_strcmp(data->f_list->arr[0], "exit"))
		unset_command(data->f_list->arr, data->env);
	else
		other_commands(data->f_list->arr, data->env);
}