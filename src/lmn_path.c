/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:56 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:18:56 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void				free_path(t_pth *pth)
{
	lst_free(pth->rooms, NULL);
	free(pth);
}

int					build_path(const t_lemin *lem, t_lst *br)
{
	t_node 			*entry;
	t_room 			*room;

	entry = br->first;
	while (entry->data != lem->end)
	{
		room = entry->data;
		if (room->out->length > 1)
			ft_error("find_path\troom->links > 1", -2);
		if (!room->out->length)
			return (0);
		lst_append(br, room->out->first->data);
		entry = entry->next;
	}
	return (1);
}

void 				find_path(t_lemin *lem)
{
	t_node			*node;
	t_lst			*br;
	t_pth 			*path;

	node = lem->start->out->first;
	lem->paths = lst_new();
	while (node)
	{
		br = lst_new();
		path = ft_memalloc(sizeof(t_pth));
		path->rooms = br;
		lst_append(br, node->data);
		if(!build_path(lem, br))
			free_path(path);
		else
			lst_append(lem->paths, path);
		node = node->next;
	}
	if (!lem->paths->length)
		ft_error("Error\n", -1);
}
