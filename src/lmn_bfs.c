/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:17:13 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/18 15:16:53 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		desc_level(t_room *child, t_room *parent)
{
	child->desc_level = child->desc_level > 0 &&
						child->desc_level < parent->desc_level + 1 ?
						child->desc_level :
						parent->desc_level + 1;
}

static int		bfs_rec(t_fck fck)
{
	t_node		*node;

	node = fck.get_first(fck.room);
	if (!hm_insert(fck.black, fck.room->name, fck.room))
		return (0);
	while (node)
	{
		if (!hm_lookup(fck.black, ((t_room *)node->data)->name) &&
			!qu_contains(fck.qu, node->data))
		{
			fck.f_level(node->data, fck.room);
			if (!qu_push_head(fck.qu, node->data))
				return (0);
		}
		node = node->next;
	}
	return (1);
}

void			lmt_bfs_desc(t_lemin *lem)
{
	t_hm		*black;
	t_qu		*qu;

	lem->end->desc_level = 0;
	if (!(qu = qu_new())
		|| !(black = hm_new(&ft_str_hash, (t_fequal) & ft_strequ))
		|| !(qu_push_head(qu, lem->end))
		|| !(hm_insert(black, lem->start->name, lem->start)))
		ft_error("Allocation error\n", -1);
	while (!qu_is_empty(qu))
		if (!bfs_rec((t_fck)
				{qu_pop_tail(qu), black, qu, &desc_level, &get_in_first}))
			ft_error("Allocation error\n", -1);
	hm_free(black, NULL, NULL);
	qu_free(qu);
	lem->start->desc_level = INT_MAX;
}
