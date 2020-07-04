/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:54:52 by cmeowth           #+#    #+#             */
/*   Updated: 2020/07/04 15:45:01 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char				*ft_itoa_static(int nbr)
{
	static char		str[12];
	size_t			length;

	length = ft_silen(nbr, 10);
	str[length] = '\0';
	if (nbr == 0)
		str[0] = '0';
	else if (nbr == INT_MIN)
		ft_strcpy(str, "-2147483648");
	else if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		str[--length] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
