/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:47:11 by iouardi           #+#    #+#             */
/*   Updated: 2022/06/06 02:06:03 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_sara/minishell.h"

void    echo_command(char **arr)// need to add a new line and space between args
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
	}//doesn't fail n always returns a big fat 0
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
		//returns 1 in case of an error and 0 when it's working
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

void	export_command(char **arr, t_env *env)//  need to handle the space after the name and before the equal
{
	int		i;
	char	**arg_splited;
	int		flag;

	i = 1;
	// if (!arr[1] || arr[2])
	if (!arr[1] || !ft_strlen(arr[1]))
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

char	**linked_list_to_table(t_env *env)
{
	t_env	*tmp;
	char	**arr;
	int		i;

	tmp = env;
	i = 0;
	arr = malloc(sizeof(char *) * ft_lstsize_env(tmp));
	while (tmp)
	{
		arr[i] = ft_strjoin(tmp->name, "=");
		arr[i] = ft_strjoin(arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = 0;
	return (arr);
}

void	free_all(char **cmd_temp1)
{
	int		i;

	i = 0;
	while (cmd_temp1[i])
	{
		free (cmd_temp1[i]);
		cmd_temp1[i] = NULL;
		i++;
	}
	free (cmd_temp1);
}

void	print_error(char *cmd)
{
	char	*err;

	err = strerror (errno);
	ft_putstr_fd("shell: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
}

void	other_commands(t_data *data, t_tools *tool)
{
	if (!check_path(data->f_list->arr[0]) || check_path(data->f_list->arr[0]) == 2)
		tool->path = ft_strdup(data->f_list->arr[0]);
	else
		tool->path = find_path(data->env, data->f_list->arr[0]);
	if (!tool->path)
	{
		write(2, "command not found\n", 19);
		exit(1);
	}
	execve(tool->path, data->f_list->arr, linked_list_to_table(data->env));
	free_all(data->f_list->arr);
	print_error(data->f_list->arr[0]);
	exit(1);
}

void	check_fd1(int fd1, t_list *tmp)
{
	if (fd1 < 0)
	{
		tmp = tmp->next;
		write(2, "shell: no such file or directory\n", 34);
	}
	dup2(fd1, 0);
}

int	before_execution(t_data *data, t_list *tmp, t_tools *tool)
{
	// int 	fd1;
	int		pid;

	// printf("---------------infile = %s-----------\n", tmp->infile);
	write (2, tmp->infile, ft_strlen(tmp->infile));
	// if (tmp->infile)
	// 	fd1 = open (tmp->infile, O_RDONLY, 0666);
	// else
	// 	fd1 = 0;
	// check_fd1(fd1, tmp);
	if (pipe(tool->p) == -1)
		exit (1);//not sure of the return value
	pid = fork();
	if (pid == 0)
	{
		close(tool->p[0]);
		dup2(tool->p[1], 1);
		close(tool->p[1]);
		if (!ft_strcmp(tmp->arr[0], "echo"))
			echo_command(tmp->arr);
		else if (!ft_strcmp(tmp->arr[0], "cd"))
			cd_command(tmp->arr, data->env);
		else if (!ft_strcmp(tmp->arr[0], "pwd"))
			pwd_command();
		else if (!ft_strcmp(tmp->arr[0], "export"))
			export_command(tmp->arr, data->env);
		else if (!ft_strcmp(tmp->arr[0], "env"))
			env_command(tmp->arr, data->env);
		else if (!ft_strcmp(tmp->arr[0], "unset"))
			unset_command(tmp->arr, data->env);
		// else if (!ft_strcmp(tmp->arr[0], "exit"))
		// 	unset_command(tmp->arr, data->env);
		else
			other_commands(data, tool);
	}
	else
	{
		close(tool->p[1]);
		dup2(tool->p[0], 0);
		close(tool->p[0]);
	}
	return (pid);
}

void	last_command_(t_tools *tool, int fd, t_data *data, char *path_temp)
{
	printf("----------data->f_list = %s---------\n", data->f_list->infile);
	printf("--data->f_list->output = %s---------\n", data->f_list->output);
	dup2(fd, 1);
	execve(tool->path, data->f_list->arr, linked_list_to_table(data->env));
	print_error(data->f_list->arr[0]);
	free(path_temp);
}

void	check_fd(int fd)
{
	if (fd == -1)
	{
		write(2, "no such file or directory\n", 27);
		exit(1);
	}
}


void	free_o_ziid_free(t_tools *tool)
{
	free(tool->path);
}

int	last_command(t_tools *tool, t_list *tmp, t_data *data)
{
	int		fd;
	// char	*path_temp;
	int		pid;

	// printf("-------------------fd1 = %d---------\n", fd1);
	if (!check_path(tmp->arr[0]) || check_path(tmp->arr[0]) == 2)
		tool->path = ft_strdup(tmp->arr[0]);
	else
		tool->path = find_path(data->env, tmp->arr[0]);
	if (!tool->path)
	{
		write(2, "command not found\n", 19);
		exit(1);
	}
	// if (check_here_doc(argv[1]))
	// 	fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (tmp->output)
		fd = open(tmp->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = 1;
	check_fd(fd);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		// printf("----------data->f_list = %s---------\n", data->f_list->infile);
		// printf("--data->f_list->output = %s---------\n", tmp->output);
		return (last_command_(tool, fd, data, tool->path), pid);
	}
	else
		return (free_o_ziid_free(tool), pid);
	// return (pid);
}

void	close_n_wait(t_tools *tool, int *pid)
{
	int		i;

	i = 0;
	close(tool->p[0]);
	close(tool->p[1]);
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	execute_commands(t_data	*data)
{
	t_list	*tmp;
	t_tools *tool;
	int		*pid;
	int		i;
	int		fd1;

	i = 0;
	tool = malloc (sizeof(t_tools));
	tmp = data->f_list;
	pid = malloc(sizeof(int) * ft_lstsize(data->f_list));
	if (tmp->infile)
		fd1 = open (tmp->infile, O_RDONLY, 0666);
	else
		fd1 = 0;
	check_fd1(fd1, tmp);
	while (tmp->next)
	{
		pid[i++] = before_execution(data, tmp, tool);
		tmp = tmp->next;
	}
	pid[i] = last_command(tool, tmp, data);
	close_n_wait(tool, pid);
}