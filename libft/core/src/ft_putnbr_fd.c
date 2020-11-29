/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 08:46:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/coreft.h"

void	ft_putnbr_fd(int fd, int nbr)
{
	unsigned int n;

	if (nbr < 0)
	{
		ft_putchar_fd(fd, '-');
		n = nbr * -1;
	}
	else
	{
		n = nbr;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(fd, n / 10);
	}
	ft_putchar_fd(fd, n % 10 + '0');
}
