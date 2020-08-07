/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_alight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:05:51 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:05:51 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static	void		alight(t_room *room)
{
	t_node			*node;
	t_node			*next;
	pointer			data;

	node = room->out->first;
	while (node)
	{
		data = node->data;
		next = node->next;
		if (((t_room*)data)->asc_level < room->asc_level)
		{
			lst_rm_data(room->out, (f_equal)&room_equals, data);
			lst_rm_data(((t_room *)data)->in, (f_equal)&room_equals, room);
		}
		node = next;
	}
}

void				lmn_alight(const t_lst *lst)
{
	t_node		*node;

	node = lst->first;
	while (node)
	{
		alight(node->data);
		node = node->next;
	}
}
