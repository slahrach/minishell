/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:45:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/16 00:31:22 by slahrach         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char		*line;
	t_list		*list;
	t_list		*f_list;
	t_env		*env;
}	t_data;

char		*find_prompt(void);
char		*expansion(char *token);
void		error(int a);
void		to_parse(char *line, t_list **list);
int			is_whitespace(char c);
char		*non_quoting(int *i, char *line, t_list **list);
char		*handle_quoting(int	*i, char *line, t_list **list);
char		*expansion(char *token);
int			is_special(char c);
char		*chr_to_str(char c);
int			builtins(t_list *f_list, char **env);
t_list		*devide(t_list *list);
t_env		*find_last(t_env *lst);
void		add_front(t_env **lst, t_env *new);
void		add_back(t_env **lst, t_env *new);
int			sizelst(t_env *lst);
t_env		*new_node(char *name, char *value);
void		set_env(char **envp, t_env **env);
#endif