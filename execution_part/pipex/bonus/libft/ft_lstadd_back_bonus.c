/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 22:55:45 by iouardi           #+#    #+#             */
/*   Updated: 2021/11/18 04:31:56 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*arr;

	if (new != NULL)
	{
		if (ft_lstsize(*(lst)) > 0)
		{
			arr = ft_lstlast(*lst);
			arr->next = new;
		}
		else
			ft_lstadd_front(lst, new);
	}
}
