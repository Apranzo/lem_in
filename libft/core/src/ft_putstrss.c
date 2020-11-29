/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrss.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 21:03:13 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

void	ft_putstrss(char **ar, int c)
{
	ft_putstrss_fd(1, ar, c);
}

void	ft_putstrss_fd(int fd, char **ar, int c)
{
	if (c < 0)
		c = '\n';
	while (*ar)
	{
		ft_putstr_fd(fd, *ar);
		ft_putchar_fd(fd, c);
		ar++;
	}
}
