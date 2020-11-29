/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:53:57 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_common(const char *format, t_info *info)
{
	if (!format)
		return (-1);
	while (*format)
	{
		if (buffer_full(&info->buffer) == 1)
			info->buffer.flush_buf(&info->buffer);
		if (*format == '%')
		{
			format++;
			parsing(&format, info);
			if (*format == 0)
				break ;
		}
		else
			write_char(&info->buffer, *format);
		++format;
	}
	if (info->buffer.index != 0)
		info->buffer.flush_buf(&info->buffer);
	return (info->buffer.length);
}

int				ft_printf(const char *format, ...)
{
	t_info		info;
	int			len;

	initialize_buffer(1, &info.buffer);
	info.buffer.flush_buf = (t_fflush) & print_buffer;
	va_start(info.ap, format);
	len = ft_common(format, &info);
	va_end(info.ap);
	return (len);
}

int				ft_vfprintf(int fd, const char *format, ...)
{
	t_info		info;
	int			len;

	initialize_buffer(fd, &info.buffer);
	info.buffer.flush_buf = (t_fflush) & print_buffer;
	va_start(info.ap, format);
	len = ft_common(format, &info);
	va_end(info.ap);
	return (len);
}
