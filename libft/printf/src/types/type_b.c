/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:52:00 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		specs_handler(t_info *info, uintmax_t number)
{
	if (number == 0)
		info->hash = 0;
	info->plus = 0;
	info->space = 0;
	info->precision = 0;
}

void			type_b(const char **format, t_info *info)
{
	uintmax_t	number;
	t_data		data;

	info->type = **format;
	get_ui(&number, info);
	specs_handler(info, number);
	if (number == 0)
		data.str = "0";
	else
		data.str = ft_sitoa_base_static(number, 2, ft_isupper(info->type));
	if (info->hash == 1)
		data.prefix = ft_isupper(info->type) ? "0B" : "0b";
	data.length = ft_strlen(data.str);
	data.negative = 0;
	apply_specs(info, &data);
}
