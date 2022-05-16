/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:11:05 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/16 18:31:56 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
	}
	free(arr);
}

void	ft_lstclear1(t_list **lst)
{
	t_list	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->append)
			free((*lst)->append);
		if ((*lst)->infile)
			free((*lst)->infile);
		if ((*lst)->output)
			free((*lst)->output);
		if ((*lst)->delimiter)
			free((*lst)->delimiter);
		ft_lstclear(&(*lst)->inside);
		free_arr((*lst)->arr);
		free(*lst);
		*lst = temp;
	}
	lst = NULL;
}
