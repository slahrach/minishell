/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:00:36 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/18 18:23:23 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_prompt(t_data *data)
{
	char	*folder;
	char	*user;
	char	*prompt;

	folder = ft_getenv(&data->env, "PWD");
	user = ft_getenv(&data->env, "USER");
	if (ft_strrchr(folder, '/'))
		folder = ft_strrchr(folder, '/') + 1;
	folder = ft_strjoin ("\033[1;33m", folder);
	folder = ft_strjoin1 (folder, "\033[0m");
	user = ft_strjoin ("\033[1;31m", user);
	user = ft_strjoin1 (user, "\033[0m");
	prompt = ft_strjoin ("\033[1;33m* {\033[0m", user);
	free(user);
	prompt = ft_strjoin1 (prompt, "\033[1;33m} \033[0m");
	prompt = ft_strjoin1 (prompt, folder);
	free(folder);
	prompt = ft_strjoin1 (prompt, "\033[1;31m $ \033[0m");
	return (prompt);
}

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '<')
		return (INPUT);
	if (c == '>')
		return (OUTPUT);
	if (c == '|')
		return (PIPE);
	return (0);
}

char	*chr_to_str(char c)
{
	char	*str;

	str = malloc (2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_list	*_new(void)
{
	t_list	*new;

	new = malloc (sizeof (t_list));
	new->inside = NULL;
	new->exit_status = 0;
	new->err = 0;
	new->next = NULL;
	new->pipe_after = 0;
	new->fd_in = 0;
	new->fd_out = 0;
	new->pipe_before = 0;
	new->redirect = NULL;
	new->arr = NULL;
	new->content = NULL;
	return (new);
}
