/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:45:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/10 14:47:56 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <signal.h>
# define INPUT 1
# define OUTPUT 2
# define PIPE 3
# define APPEND 5
# define DELIMITER 4
# define STATUS 6

int	g_last_exitstatus;

typedef struct s_data
{
	int			error;
	int			status;
	char		*line;
	t_list		*list_token;
	t_list		*f_list;
	t_env		*env;
	t_tools		*tool;
}	t_data;

char		*find_prompt(t_env *env);
void		error(t_data *data, int a);
void		error_delimiter(t_list **head, t_data *data, int a);
void		tokenize(char *line, t_data *data, t_env *env);
char		*expansion(t_data *data, char *token, t_env *env);
int			is_whitespace(char c);
char		*non_quoting(int *i, char *line, t_data *data, t_env *env);
char		*handle_quoting(int	*i, char *line, t_data *data, t_env *env);
int			is_special(char c);
int			check_special(int *i, char *line, int id, t_list **list);
char		*chr_to_str(char c);
int			builtins(t_list *f_list, t_env **env);
t_list		*parse(t_data *data, t_list **list);
t_env		*find_last(t_env *lst);
void		add_front(t_env **lst, t_env *new);
void		add_back(t_env **lst, t_env *new);
int			sizelst(t_env *lst);
t_env		*new_node(char *name, char *value, int flag);
t_list		*_new(void);
void		set_env(char **envp, t_env **env);
char		*ft_getenv(t_env *env, char *name);
void		env_add_change(t_env **env, char *name, char *value, int flag);
void		unset_node(t_env **env, char *name);
void		env_add_change1(t_env **env, char *name, char *value, int flag);

/********************execution*******************************/

void		execute_commands(t_data	*data);
void		exit_command(t_data *data, t_list **f_list);
int			exit_status_command(t_data *data);
void		print_status(t_data *data);
void		echo_command(t_list **list);
void		pwd_command(t_list **list);
void		env_command(t_list **list, t_env *env);
void		unset_command(t_list **list, t_env *env);
int			parse_args(t_list **list, char *var);
void		cd_command(t_list **list, t_env *env);
void		export_command(t_list **list, t_env *env);
void		other_commands(t_data *data, t_list *tmp, t_tools *tool);
void		check_builtins_or_other_cmd(t_data *data, t_list *tmp);
int			check_builtins(t_data *data, t_list *tmp);
int			check_path(char *path);
char		*find_path(t_env *env, char	*cmd);
void		print_error(char *cmd);
int			ft_lstsize_env(t_env *lst);
char		**linked_list_to_table(t_env *env);
void		here_doc(t_redir *tmp, t_tools *tool);
char		*get_next_line(int fd);

#endif