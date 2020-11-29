/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_specs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:50:15 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** get_number() calculates and return an integer.
*/

static int		get_number(const char **format)
{
	int			number;

	number = 0;
	while (ft_isdigit(**format))
	{
		number = (number * 10) + (**format - '0');
		(*format)++;
	}
	return (number);
}

/*
** digit() while parsing the formated string if previous character was not
** a '.' it is necessarily a width, so set_width() is called.
*/

void			digit(const char **format, t_info *info)
{
	if (*(*format - 1) != '.')
		set_width(format, info);
}

/*
** set_width() calls get_number() to assign pointer to width specificator.
*/

void			set_width(const char **format, t_info *info)
{
	info->width = get_number(format);
}

/*
** set_precision() sets flag point to 1 and calls get_number() to assign
** pointer to precision specificator.
*/

void			set_precision(const char **format, t_info *info)
{
	(*format)++;
	info->point = 1;
	info->precision = get_number(format);
}
