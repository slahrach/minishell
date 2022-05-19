/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:36:50 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/17 20:31:07 by slahrach         ###   ########.fr       */
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
	new->output = NULL;
	new->pipe_after = 0;
	new->pipe_before = 0;
	new->id = 0;
	new->next = NULL;
	return (new);
}

/*
#include <stdio.h>

int	main(void)
{
	t_list	*list;
	int		*c;
	int		*a;
	int		b;

	b = 7;
	a = &b;
	list = ft_lstnew (a);
	c = list-> content;
	printf("%d", (list->content));
	return (0);
}*/
