/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:53:57 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char				*ft_ftoa_static(double number, unsigned int precision)
{
	static char		str[10];
	int				i;
	int				i_part;
	float			f_part;

	i_part = (int)number;
	f_part = number - (i_part);
	ft_strcpy(str, ft_itoa_static(i_part));
	str[ft_nblen(i_part)] = '.';
	i = ft_nblen(i_part) + 1;
	if (number < 0)
		f_part *= -1;
	while (precision-- != 0)
	{
		f_part *= 10;
		str[i++] = ((int)f_part % 10) + '0';
	}
	str[(number > 0) ? 8 : 9] = '\0';
	return (str);
}
