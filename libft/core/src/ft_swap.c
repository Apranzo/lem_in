/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:59:23 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/15 18:45:19 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

void		ft_swap(void *a, void *b, size_t size)
{
	void	*tmp;

	if ((tmp = malloc(size)))
	{
		ft_memcpy(tmp, a, size);
		ft_memcpy(a, b, size);
		ft_memcpy(b, tmp, size);
	}
}
