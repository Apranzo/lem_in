/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:50:07 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Below are the functions that sets corresponding length of a placeholder.
*/

void	length_h(const char **format, t_info *info)
{
	if (info->length == 0)
	{
		info->length = LENGTH_H;
		if (*(*format + 1) == 'h')
		{
			info->length = LENGTH_HH;
			(*format)++;
		}
	}
	(*format)++;
}

void	length_l(const char **format, t_info *info)
{
	if (**format == 'L')
		info->length = LENGTH_LLL;
	else
	{
		info->length = LENGTH_L;
		if (*(*format + 1) == 'l')
		{
			info->length = LENGTH_LL;
			(*format)++;
		}
	}
	(*format)++;
}

void	length_j(const char **format, t_info *info)
{
	info->length = LENGTH_J;
	(*format)++;
}

void	length_z(const char **format, t_info *info)
{
	info->length = LENGTH_Z;
	(*format)++;
}

void	length_t(const char **format, t_info *info)
{
	info->length = LENGTH_T;
	(*format)++;
}
