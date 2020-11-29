/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeowth <cmeowth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 03:54:13 by cmeowth           #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** parsing() initialize specificators and calls for each printable character
** a function pointer g_jump_table until the placeholder type is defined.
*/

void				parsing(const char **format, t_info *info)
{
	info->type = 0;
	initialize_specs(info);
	while (**format && info->type == 0)
		if (ft_isprint(**format))
			g_jump_table[**format - ' '](format, info);
}
