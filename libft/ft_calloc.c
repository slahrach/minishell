/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 21:32:37 by slahrach          #+#    #+#             */
/*   Updated: 2021/11/20 21:42:48 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	a;

	a = count * size;
	ptr = (void *) malloc (a);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, a);
	return (ptr);
}
/*
int main()
{
    int size = 8539;

	void * d1 = ft_calloc(size, sizeof(int));
	void * d2 = calloc(size, sizeof(int));
	if (memcmp(d1, d2, size * sizeof(int)))
		exit(printf("TEST_FAILED"));
	free(d1);
	free(d2);
	exit(printf("TEST_SUCCESS"));
}*/
