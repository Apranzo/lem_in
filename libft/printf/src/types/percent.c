/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:51:51 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		specs_handler(t_info *info)
{
	info->hash = 0;
	info->plus = 0;
	info->space = 0;
	info->precision = 0;
}

void			percent(const char **format, t_info *info)
{
	t_data		data;

	info->type = **format;
	data.str = "%";
	data.length = 1;
	data.negative = 0;
	specs_handler(info);
	apply_specs(info, &data);
}
