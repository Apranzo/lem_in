/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base_static.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:20:40 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char				*ft_uitoa_base_static(uintmax_t number, int base,
					int uppercase)
{
	static char		str[11];
	size_t			length;

	if (base < 2 || base > 36)
		return (NULL);
	length = ft_uilen(number, base);
	str[length] = '\0';
	if (number == 0)
		str[0] = '0';
	else if (uppercase == 1)
		while (number > 0)
		{
			str[--length] = BASE_UPPER[number % base];
			number /= base;
		}
	else
		while (number > 0)
		{
			str[--length] = BASE_LOWER[number % base];
			number /= base;
		}
	return (str);
}
