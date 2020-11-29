/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 23:54:56 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

char			*ft_litoa(intmax_t number)
{
	char		*str;
	size_t		length;

	if (number <= LLONG_MIN)
	{
		str = ft_strdup("-9223372036854775808");
		return (str);
	}
	length = ft_silen(number, 10);
	if (!(str = ft_strnew(length)))
		return (NULL);
	if (number == 0)
		str[0] = '0';
	else if (number < 0)
	{
		str[0] = '-';
		number *= -1;
	}
	while (number > 0)
	{
		str[--length] = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}
