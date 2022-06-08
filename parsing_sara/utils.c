/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:00:36 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/08 00:00:01 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_prompt(t_env *env)
{
	char	*folder;
	char	*user;
	char	*prompt;

	folder = ft_getenv(env, "PWD");
	user = ft_getenv(env, "USER");
	if (ft_strrchr(folder, '/'))
		folder = ft_strrchr(folder, '/') + 1;
	folder = ft_strjoin ("\033[1;33m", folder);
	folder = ft_strjoin1 (folder, "\033[0m");
	if (ft_strchr(user, '='))
		user = ft_strchr(user, '=') + 1;
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
