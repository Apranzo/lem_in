/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_del_output_forks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:42 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:18:42 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static	void		del_output_forks(t_room	*room)
{
	t_node			*node;
	int				shortest;

	shortest = INT_MAX;
	node = room->out->first;
	while (!room->required && node)
	{
		shortest = ((t_room *) node->data)->desc_level > 0 &&
				   shortest > ((t_room *) node->data)->desc_level ?
				   ((t_room *) node->data)->desc_level :
				   shortest;
		node = node->next;
	}
	node = room->out->first;
	while (node && !room->required && room->out->length > 1)
	{
		if (shortest < 0 || ((t_room *) node->data)->desc_level != shortest)
			node = lst_rm_entry(room->out, node);
		else
			(shortest = -1) && (node = node->next);
	}
	if (!room->required && room->out->length > 1)
		ft_error("del_output_forks\troom->links.length > 1", -2);
}

void				lmn_del_output_forks(const t_lst *lst)
{
	t_node		*node;

	node = lst->first;
	while (node)
	{
		del_output_forks(node->data);
		node = node->next;
	}
}