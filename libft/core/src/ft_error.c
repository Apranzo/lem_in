/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:41:45 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

void	ft_error_fd(int fd, char *mes, int code)
{
	write(fd, mes, ft_strlen(mes));
	write(fd, "\n", 1);
	exit(code);
}

void	ft_error(char *mes, int code)
{
	ft_error_fd(2, mes, code);
}
