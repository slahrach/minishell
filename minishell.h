/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 05:45:06 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 21:31:51 by slahrach         ###   ########.fr       */
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

typedef struct s_data
{
	char	*line;
	t_list	*list;
}	t_data;

const char	*find_prompt(void);
char		*expansion(char *token);
void		error(int a);
void		to_parse(char *line, t_list **list);
int			is_whitespace(char c);
char		*non_quoting(int *i, char *line);
char		*handle_quoting(int	*i, char *line);

#endif