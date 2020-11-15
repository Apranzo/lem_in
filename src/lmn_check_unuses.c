/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_check_unuses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:21 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/15 15:33:17 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void			check_unuses(t_room *room)
{
	t_node			*node;
	t_node			*next;
	t_pntr			*data;

	node = room->out->first;
//	while (node)
//	{
//		next = node->next;
//		data = node->data;
//		if (room->asc_level < 0)
//		{
//			lst_rm_data(((t_room *)data)->out, (t_fequal) & room_equals, room);
//			lst_rm_data(((t_room *)data)->in, (t_fequal) & room_equals, room);
//			lst_rm_data(room->in, (t_fequal) & room_equals, data);
//			lst_rm_data(room->out, (t_fequal) & room_equals, data);
//		}
//		else if (((t_room*)node->data)->asc_level == room->asc_level)
//		{
//			lst_rm_data(room->in, (t_fequal) & room_equals, data);
//			lst_rm_data(((t_room *)data)->out, (t_fequal) & room_equals, room);
//			lst_rm_data(room->out, (t_fequal) & room_equals, data);
//			lst_rm_data(((t_room *)data)->in, (t_fequal) & room_equals, room);
//		}
//		node = next;
//	}
}

void				lmn_check_unuses(const t_lst *lst)
{
	t_node			*node;

	node = lst->first;
	while (node)
	{
		check_unuses(node->data);
		node = node->next;
	}
}
