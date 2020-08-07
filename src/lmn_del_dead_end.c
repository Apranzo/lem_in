/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_del_dead_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:29 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:18:29 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static	void 		delete_dead_end(t_room	*room)
{
	t_node 			*node;
	t_node 			*tmp;
	pointer			data;

	if (!room->required && room->in->length && !room->out->length)
	{
		node = room->in->first;
		while (node)
		{
			data = node->data;
			tmp = node->next;
			lst_rm_data(((t_room*)data)->out, (f_equal) &room_equals, room);
			lst_rm_data(room->in, (f_equal) &room_equals, data);
			node = tmp;
		}
	}
	node = room->out->first;
	while (!room->required && !room->in->length && room->out->length)
	{
		data = node->data;
		tmp = node->next;
		lst_rm_data(((t_room*)data)->in, (f_equal) &room_equals, room);
		lst_rm_data(room->out, (f_equal) &room_equals, data);
		node = tmp;
	}
}

void				lmn_del_dead_end(const t_lst *lst)
{
	t_node		*node;

	node = lst->first;
	while (node)
	{
		delete_dead_end(node->data);
		node = node->next;
	}
}