/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 01:43:32 by slahrach          #+#    #+#             */
/*   Updated: 2022/04/28 08:19:13 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	int		i;
	t_list	*lst;

	lst = NULL;
	i = 0;
	to_parse("'\"'ls'\"'", &lst);
	while (lst)
	{
		//printf("%d\n", i);
		printf("%s\n", lst->content);
		lst = lst->next;
		i++;
	}
}
