/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_si.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:50:56 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	get_si(intmax_t *number, t_info *info)
{
	if (ft_isupper(info->type) || info->length & (LENGTH_J | LENGTH_LL))
		*number = (intmax_t)va_arg(info->ap, intmax_t);
	else if (info->length == 0 || info->length & LENGTH_T)
		*number = (int)va_arg(info->ap, int);
	else if (info->length & LENGTH_H)
		*number = (short int)va_arg(info->ap, int);
	else if (info->length & LENGTH_HH)
		*number = (signed char)va_arg(info->ap, int);
	else if (info->length & LENGTH_L)
		*number = (long int)va_arg(info->ap, long int);
	else if (info->length & LENGTH_Z)
		*number = (size_t)va_arg(info->ap, size_t);
}
