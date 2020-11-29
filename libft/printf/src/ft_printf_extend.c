/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_extend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 20:08:06 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		flush_to_str(t_buffer *bf)
{
	char		*str;
	char		*new;
	size_t		len;

	str = bf->out;
	len = str ? ft_strlen(str) : 0;
	if (!(new = ft_strnew(len + bf->index + 1)))
		return (-1);
	if (str)
		ft_memcpy(new, str, len);
	ft_memcpy(new + len, bf->content, bf->index);
	bf->out = new;
	free(str);
	len = bf->index + 1;
	bf->index = 0;
	return (len);
}

int				ft_sprintf(char **str, const char *format, ...)
{
	t_info		info;
	int			len;

	va_start(info.ap, format);
	initialize_buffer(0, &info.buffer);
	info.buffer.out = *str;
	info.buffer.flush_buf = (t_fflush) & flush_to_str;
	len = ft_common(format, &info);
	*str = info.buffer.out;
	va_end(info.ap);
	return (len);
}

static int		flush_to_strbld(t_buffer *bf)
{
	t_str_bld	*bld;
	size_t		len;

	bld = bf->out;
	sb_append_len(bld, bf->content, bf->index);
	len = bf->index + 1;
	bf->index = 0;
	return (len);
}

int				ft_sbprintf(t_str_bld *str, const char *format, ...)
{
	t_info		info;
	int			len;

	va_start(info.ap, format);
	initialize_buffer(0, &info.buffer);
	info.buffer.out = str;
	info.buffer.flush_buf = (t_fflush) & flush_to_strbld;
	len = ft_common(format, &info);
	va_end(info.ap);
	return (len);
}
