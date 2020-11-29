/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uilen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:21:45 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

size_t		ft_uilen(uintmax_t number, int base)
{
	size_t	length;

	length = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number /= base;
		++length;
	}
	return (length);
}
