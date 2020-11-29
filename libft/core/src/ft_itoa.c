/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:29:32 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

static char			*numbirating(unsigned int un, char *str)
{
	while (un > 0)
	{
		*str = un % 10 + '0';
		if (un >= 10)
			str--;
		un /= 10;
	}
	return (str);
}

char				*ft_itoa(int n)
{
	char			*num;
	int				underzero;
	unsigned int	un;
	int				intlen;

	un = 0;
	underzero = n < 0;
	if (underzero)
		un = un - n;
	else
		un = n;
	intlen = ft_intlen(n);
	if (!(num = ft_strnew(sizeof(char) * intlen)))
		return (NULL);
	num = numbirating(un, num + intlen - 1);
	if (un == 0)
		num[0] = un + '0';
	num -= underzero;
	if (underzero)
		*num = '-';
	return (num);
}
