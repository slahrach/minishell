/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 06:00:36 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 20:56:06 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*find_prompt(void)
{
	const char	*folder = NULL;
	const char	*user = NULL;
	const char	*prompt = NULL;

	folder = getenv("PWD");
	user = getenv("USER");
	if (ft_strrchr(folder, '/'))
		folder = ft_strrchr(folder, '/') + 1;
	folder = (const char *) ft_strjoin ("\033[1;33m", folder);
	folder = (const char *) ft_strjoin (folder, "\033[0m");
	if (ft_strchr(user, '='))
		user = ft_strchr(user, '=') + 1;
	user = (const char *) ft_strjoin ("\033[1;31m", user);
	user = (const char *) ft_strjoin (user, "\033[0m");
	prompt = (const char *) ft_strjoin ("\033[1;33m* {\033[0m", user);
	prompt = (const char *) ft_strjoin (prompt, "\033[1;33m} \033[0m");
	prompt = (const char *) ft_strjoin (prompt, folder);
	prompt = (const char *) ft_strjoin (prompt, "\033[1;31m $ \033[0m");
	return (prompt);
}

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
