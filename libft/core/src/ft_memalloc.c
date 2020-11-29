/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:34:01 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

void	*ft_memalloc(size_t size)
{
	void *area;

	area = malloc(size);
	if (area)
		ft_bzero(area, size);
	return (area);
}

void	*ft_tmemalloc(size_t type_size, size_t amount)
{
	return (ft_memalloc(type_size * amount));
}

void	*ft_tmalloc(size_t type_size, size_t amount)
{
	return (malloc(type_size * amount));
}
