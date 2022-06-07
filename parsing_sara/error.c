/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:37:47 by slahrach          #+#    #+#             */
/*   Updated: 2022/06/07 04:36:38 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_data *data, int a)
{
	if (a == 0)
	{
		write (2, "Error\nsyntax error !\n", 21);
		data->last_exitstatus = 258;
		data->error = 1;
	}
	if (a == 1)
	{
		write (2, "Error\nunclosed quotes !\n", 24);
		data->last_exitstatus = 2;
		data->error = 1;
	}
}
