/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:36:50 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/07 00:32:39 by slahrach         ###   ########.fr       */
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
	new->append = NULL;
	new->delimiter = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->pipe_after = 0;
	new->pipe_before = 0;
	new->id = 0;
	new->next = NULL;
	return (new);
}

t_redir	*redir_new(char	*content)
{
	t_redir	*new;

	new = (t_redir *) malloc (sizeof (t_redir));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}