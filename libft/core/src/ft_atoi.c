/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:35:47 by cshinoha          #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/coreft.h"

int				ft_atoi(const char *str)
{
	int			positive;
	size_t		nbr;

	nbr = 0;
	positive = 1;
	while (ft_iswhite(*str))
		str++;
	if (*str == '-')
	{
		positive = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * positive);
}
