/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:30:27 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/string_builder.h"

t_str_bld			*sb_create(char *str)
{
	t_str_bld		*bld;

	if (!(bld = ft_memalloc(sizeof(t_str_bld)))
		|| !(bld->fragments = lst_new()))
		return (NULL);
	if (str && *str)
		sb_append(bld, str);
	return (bld);
}

static void			str_free(t_str *str)
{
	free(str->str);
	free(str);
}

void				sb_reset(t_str_bld *sb)
{
	lst_clear(sb->fragments, (t_ffree) & str_free);
	sb->concated = NULL;
	sb->len = 0;
}

void				sb_free(t_str_bld *sb)
{
	lst_free(sb->fragments, (t_ffree) & str_free);
	sb->concated = NULL;
	sb->len = 0;
	free(sb);
}
