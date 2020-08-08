/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:51 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 17:51:10 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_hash.h"

size_t				ft_str_hash(t_pntr pointer)
{
	size_t			result;
	unsigned char	*p;

	result = 5381;
	p = (unsigned char *) pointer;
	while (*p != '\0')
	{
		result = (result << 5) + result + *p;
		++p;
	}
	return (result);
}

size_t				int_hash(t_pntr pointer)
{
	return ((size_t) pointer);
}

size_t				pointer_hash(t_pntr pointer)
{
	return ((size_t) pointer);
}