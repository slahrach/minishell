/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouardi <iouardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:37:47 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/18 00:52:56 by iouardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_data *data, int a)
{
	if (a == 0)
	{
		write (2, "Error\nsyntax error !\n", 21);
		g_last_exitstatus = 258;
		data->error = 1;
	}
	if (a == 1)
	{
		write (2, "Error\nunclosed quotes !\n", 24);
		g_last_exitstatus = 1;
		data->error = 1;
	}
}

void	error_delimiter(t_list **head, t_data *data, int a)
{
	t_redir	*redi;

	redi = (*head)->redirect;
	while (redi)
	{
		if (redi->id == DELIMITER)
		{
			(*head)->err = 1;
			g_last_exitstatus = 258;
			return ;
		}
		redi = redi->next;
	}
	error(data, a);
}
