/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_shortest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:15:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/18 17:32:44 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_room		*mindesc(t_room *room, t_lemin *lem)
{
	t_room			*less;
	t_room			*edge;
	t_node			*node;

	less = NULL;
	node = room->out->first;
	while (node)
	{
		edge = node->data;
		if (!hm_lookup(lem->inpath, edge->name))
		{
			if (!less)
				less = edge;
			else
			{
				less = less->desc_level > edge->desc_level ?
						edge :
						less;
			}
		}
		node = node->next;
	}
	return (less);
}

t_lst				*shortest(t_lemin *lem)
{
	t_lst			*pth;
	t_room			*room;

	room = lem->start;
	pth = lst_new();
	while ((room = mindesc(room, lem)))
	{
		if (lst_contains(pth, (t_fequal) & room_equals, room))
			break ;
		lst_append(pth, room);
		if (room == lem->end)
			return (pth);
		else if (!(hm_insert(lem->inpath, room->name, room->name)))
			ft_error("main alloc error", -1);
	}
	lst_free(pth, NULL);
	return (NULL);
}
