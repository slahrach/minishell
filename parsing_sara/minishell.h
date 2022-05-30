/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:45:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/26 17:25:41 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include "libft/libft.h"
# include <signal.h>
# define INPUT 1
# define OUTPUT 2
# define PIPE 3
# define APPEND 5
# define DELIMITER 4

typedef struct s_data
{
	char		*line;
	t_list		*list;
	t_list		*f_list;
	t_env		*env;
}	t_data;

char		*find_prompt(void);
void		error(int a);
void		to_parse(char *line, t_list **list, t_env *env);
char		*expansion(char *token, t_env *env);
int			is_whitespace(char c);
char		*non_quoting(int *i, char *line, t_list **list, t_env *env);
char		*handle_quoting(int	*i, char *line, t_list **list, t_env *env);
int			is_special(char c);
char		*chr_to_str(char c);
int			builtins(t_list *f_list, t_env **env);
t_list		*devide(t_list **list);
t_env		*find_last(t_env *lst);
void		add_front(t_env **lst, t_env *new);
void		add_back(t_env **lst, t_env *new);
int			sizelst(t_env *lst);
t_env		*new_node(char *name, char *value, int flag);
void		set_env(char **envp, t_env **env);
char		*ft_getenv(t_env *env, char *name);
void		env_add_change(t_env **env, char *name, char *value);
void		unset_node(t_env **env, char *name);
void		env_add_change1(t_env **env, char *name, char *value);

/********************execution*******************************/

void	execute_commands(t_data	*data);
#endif