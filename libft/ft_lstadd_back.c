/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 23:49:36 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/25 20:25:54 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!(*lst))
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	last = ft_lstlast(*lst);
	if (new->next == NULL)
		last->next = new;
	while (new->next != NULL)
	{
		last->next = new;
		new = new->next;
	}
}
/*
#include <stdio.h>

int main()
{
	t_list * l =  NULL; t_list * l2 =  NULL; 
        ft_lstadd_back(&l, ft_lstnew("1"));
        printf("%s\n", (l->content));
        //printf("%s\n", l->next);

        ft_lstadd_back(&l, ft_lstnew("2"));
        printf("%s\n", (l->content));
		printf("%s\n", (l->next->content));
        //printf("%s\n", (l->next->next));

        ft_lstadd_back(&l2, ft_lstnew("3"));
        ft_lstadd_back(&l2, ft_lstnew("4"));
        ft_lstadd_back(&l, l2);
		printf("%s\n", (l->content));
		printf("%s\n", (l->next->content));
		printf("%s\n", (l->next->next->content));
		printf("%s\n", (l->next->next->next->content));
		//printf("%s\n", (l->next->next->next->next));
}*/
