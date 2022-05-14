/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:37:47 by slahrach          #+#    #+#             */
/*   Updated: 2022/05/14 01:52:41 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(int a)
{
	if (a == 0)
		perror("Error\nunclosed quotes ! ");
	else if (a == 1)
		perror("Error\n commande failed ! ");
	else if (a == 2)
		perror("Error\n changing directory failed ! ");
	else if (a == 3)
		perror("Error\ntoo many arguments to pwd ! ");
	else if (a == 4)
		perror("Error\nsyntax error ! ");
	exit (0);
}
