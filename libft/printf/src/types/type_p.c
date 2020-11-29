/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:52:46 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		specs_handler(t_info *info)
{
	info->hash = 0;
	info->plus = 0;
}

void			type_p(const char **format, t_info *info)
{
	uintmax_t	number;
	t_data		data;

	info->type = **format;
	specs_handler(info);
	number = va_arg(info->ap, uintmax_t);
	data.str = (number == 0 && info->point == 1 && info->precision == 0)
				? "\0"
				: ft_uitoa_base_static(number, 16, ft_isupper(info->type));
	data.length = ft_strlen(data.str);
	data.prefix = "0x";
	data.negative = 0;
	apply_specs(info, &data);
}
