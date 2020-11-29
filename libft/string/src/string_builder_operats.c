/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder_operats.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 20:01:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/string_builder.h"

int					sb_append_len(t_str_bld *sb, char *str, size_t len)
{
	t_str			*frag;

	if (str && *str)
	{
		if (!(frag = (t_str *)malloc(sizeof(t_str)))
			|| !(frag->str = malloc(len)))
			return (-1);
		frag->length = len;
		ft_memcpy(frag->str, str, len);
		lst_append(sb->fragments, frag);
		sb->len += len;
	}
	return (sb->len);
}

int					sb_append(t_str_bld *sb, char *str)
{
	return (sb_append_len(sb, str, ft_strlen(str)));
}

char				*sb_concat(t_str_bld *sb)
{
	char			*cursor;
	t_str			*str;
	t_node			*node;

	if (sb->concated)
		return (sb->concated);
	if (!(sb->concated = (char *)ft_tmalloc(sizeof(char), sb->len + 1)))
		return (NULL);
	cursor = sb->concated;
	node = sb->fragments->first;
	while (node)
	{
		str = node->data;
		ft_memcpy(cursor, str->str, str->length);
		cursor += str->length;
		node = node->next;
	}
	*cursor = '\0';
	return (sb->concated);
}

void				sb_repl_by_ind(t_str_bld *bld, size_t ind, char c)
{
	t_node			*node;
	size_t			cur_ind;
	t_str			*fragment;

	node = bld->fragments->first;
	cur_ind = 0;
	while (node)
	{
		fragment = node->data;
		if (fragment->length + cur_ind > ind)
		{
			fragment->str[ind - cur_ind] = c;
			return ;
		}
		else
		{
			cur_ind += fragment->length;
			node = node->next;
		}
	}
}

char				sb_by_ind(t_str_bld *bld, size_t ind)
{
	t_node			*node;
	size_t			cur_ind;
	t_str			*fragment;

	node = bld->fragments->first;
	cur_ind = 0;
	while (node)
	{
		fragment = node->data;
		if (fragment->length + cur_ind > ind)
			return (fragment->str[ind - cur_ind]);
		cur_ind += fragment->length;
		node = node->next;
	}
	return ('\0');
}
