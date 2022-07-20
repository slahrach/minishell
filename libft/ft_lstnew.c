/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:36:50 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/20 04:15:44 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->arr = NULL;
	new->inside = NULL;
	new->redirect = NULL;
	new->pipe_after = 0;
	new->pipe_before = 0;
	new->id = 0;
	new->next = NULL;
	return (new);
}

t_redir	*redir_new(char	*content, int id)
{
	t_redir	*new;

	new = (t_redir *) malloc (sizeof (t_redir));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->id = id;
	new->next = NULL;
	return (new);
}

t_fds	*new_fds(int fd)
{
	t_fds	*new;

	new = (t_fds *) malloc(sizeof(t_fds));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}
