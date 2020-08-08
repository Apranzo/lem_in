/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_alight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:05:51 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 16:12:10 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static	void		alight(t_room *room)
{
	t_node			*node;
	t_node			*next;
	t_pntr			data;

	node = room->out->first;
	while (node)
	{
		data = node->data;
		next = node->next;
		if (((t_room*)data)->asc_level < room->asc_level)
		{
			lst_rm_data(room->out, (t_fequal)&room_equals, data);
			lst_rm_data(((t_room *)data)->in, (t_fequal)&room_equals, room);
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
