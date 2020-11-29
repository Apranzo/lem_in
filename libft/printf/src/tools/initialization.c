/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:51:27 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	initialize_buffer(int fd, t_buffer *buffer)
{
	buffer->index = 0;
	buffer->fd = fd;
	buffer->length = 0;
}

void	initialize_specs(t_info *info)
{
	info->width = 0;
	info->length = 0;
	info->precision = 0;
	initialize_flags(info);
}

void	initialize_flags(t_info *info)
{
	info->hash = 0;
	info->zero = 0;
	info->plus = 0;
	info->minus = 0;
	info->space = 0;
	info->point = 0;
}
