/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:53:34 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		specs_handler(t_info *info, uintmax_t number)
{
	info->space = 0;
	info->plus = 0;
	if (number == 0)
		info->hash = 0;
}

void			type_x(const char **format, t_info *info)
{
	uintmax_t	number;
	t_data		data;

	info->type = **format;
	get_ui(&number, info);
	specs_handler(info, number);
	data.negative = 0;
	if (number == 0)
		data.str = (info->point == 1 && info->precision == 0) ? "\0" : "0";
	else
		data.str = ft_uitoa_base_static(number, 16, ft_isupper(info->type));
	if (info->hash == 1)
		data.prefix = ft_isupper(info->type) ? "0X" : "0x";
	data.length = ft_strlen(data.str);
	apply_specs(info, &data);
}
