/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_del_input_forks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:36 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/15 18:45:19 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int			del_input_forks(t_room *room) {
//	t_node *node;
//	t_pntr data;
//
//	node = room->in->first;
//	while (!room->required && node) {
//		if (!((t_room *) node->data)->required && room->in->length != 1) {
//			data = node->data;
//			lst_rm_entry(room->in, node);
//			lst_rm_data(((t_room *) data)->out, (t_fequal) &room_equals, room);
//			return (1);
//		} else
//			node = node->next;
//	}
//	t_node			*node;
//	int				shortest;
//	t_pntr			data;
//
//	shortest = INT_MAX;
//	node = room->out->first;
//	while (!room->required && node)
//	{
//		shortest = ((t_room *)node->data)->asc_level > 0 &&
//				   shortest > ((t_room *)node->data)->asc_level ?
//				   ((t_room *)node->data)->asc_level :
//				   shortest;
//		node = node->next;
//	}
//	node = room->out->first;
//	while (node && !room->required && room->in->length > 1)
//	{
//		if (shortest < 0 || ((t_room *)node->data)->asc_level != shortest) {
////			node = lst_rm_entry(room->out, node);
//			data = node->data;
//			lst_rm_entry(room->in, node);
//			lst_rm_data(((t_room *) data)->out, (t_fequal) &room_equals, room);
//		}
//		else
//		{
//			shortest = -1;
//			node = node->next;
//		}
//	}
	return (0);
}

void				lmn_del_input_forks(const t_lst *lst)
{
	t_node			*node;

	node = lst->first;
	while (node)
	{
		if (del_input_forks(node->data))
		{
			lmn_del_dead_end(lst);
			node = lst->first;
		}
		else
			node = node->next;
	}
}
