/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_silen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:56:57 by cmeowth           #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

size_t		ft_silen(intmax_t number, int base)
{
	size_t	length;

	length = 0;
	if (number == 0)
		return (1);
	else if (number < 0)
		length = 1;
	while (number != 0)
	{
		number /= base;
		++length;
	}
	return (length);
}
