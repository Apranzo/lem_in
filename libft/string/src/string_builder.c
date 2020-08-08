/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:30:27 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 16:30:27 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string/includes/string_builder.h"

t_str_bld *sb_create()
{
	t_str_bld			*bld;
	if (!(bld = ft_memalloc(sizeof(t_str_bld)))
		|| !(bld->_qu = qu_new()))
		return (NULL);
	return (bld);
}

int sb_empty(t_str_bld *sb)
{
	return (qu_is_empty(sb->_qu));
}

int					sb_append(t_str_bld *sb, char *str)
{
	size_t			length;
	t_str			*frag;

	if (str && *str)
	{
		length = ft_strlen(str);
		if (!(frag = (t_str *) malloc(sizeof(t_str)))
			|| !(frag->str = ft_tmemalloc(sizeof(char), length)))
			return SB_FAILURE;

		frag->length = length;
		frag->str = str;
//		ft_memcpy((void*) &frag->str, (const void*) str, sizeof(char) * (length)); TODO maybe
		qu_push_head(sb->_qu, frag);
		sb->len += length;
	}
	return (sb->len);
}

char *sb_concat(t_str_bld *sb)
{
	char			*buffer;
	char			*cursor;
	t_str			*str;

	if(!(buffer = (char *) ft_tmalloc(sizeof(char), sb->len + 1)))
		return NULL;
	cursor = buffer;
	while (!qu_is_empty(sb->_qu))
	{
		str = qu_pop_tail(sb->_qu);
		ft_memcpy(cursor, str->str, str->length);
		cursor += str->length;
	}
	*cursor = '\0';
	return (buffer);
}

void sb_reset(t_str_bld *sb)
{
	while (!qu_is_empty(sb->_qu))
		free(qu_pop_head(sb->_qu));
	sb->len = 0;
}

void sb_free(t_str_bld *sb)
{
	sb_reset(sb);
	free(sb);
}
