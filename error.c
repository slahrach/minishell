/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:37:47 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/14 16:53:35 by slahrach         ###   ########.fr       */
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
		g_last_exitstatus = 2;
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
