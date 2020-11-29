/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:50:28 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		buffer_full(t_buffer *buffer)
{
	return (buffer->index == PRINTF_BUFF_SIZE);
}

void	print_buffer(t_buffer *buffer)
{
	write(buffer->fd, buffer->content, buffer->index);
	buffer->index = 0;
}

void	write_char(t_buffer *buffer, char c)
{
	if (buffer_full(buffer))
		buffer->flush_buf(buffer);
	buffer->content[buffer->index++] = c;
	buffer->length++;
}

void	write_str(t_buffer *buffer, char *str, int length)
{
	if (str)
		while (*str && length--)
			write_char(buffer, *str++);
}
