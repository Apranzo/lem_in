/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:49:59 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** Below are the functions that sets (and unsets) corresponding (ignored) flag.
*/

void	flag_space(const char **format, t_info *info)
{
	info->space = 1;
	(*format)++;
}

void	flag_hash(const char **format, t_info *info)
{
	info->hash = 1;
	(*format)++;
}

void	flag_plus(const char **format, t_info *info)
{
	info->plus = 1;
	info->space = 0;
	(*format)++;
}

void	flag_minus(const char **format, t_info *info)
{
	info->minus = 1;
	info->zero = 0;
	(*format)++;
}

void	flag_zero(const char **format, t_info *info)
{
	info->zero = 1;
	(*format)++;
}
