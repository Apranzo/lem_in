/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:17:13 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 20:23:55 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static void		asc_level(t_room *child, t_room *parent)
{
	child->asc_level = child->asc_level > 0 &&
						child->asc_level < parent->asc_level + 1 ?
						child->asc_level :
						parent->asc_level + 1;
}

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

void			lmn_bfs_asc(t_lemin *lem)
{
	t_hm		*black;
	t_qu		*qu;

	lem->start->asc_level = 0;
	if (!(qu = qu_new())
		|| !(black = hm_new(&ft_str_hash, &ft_strequ))
		|| !(qu_push_head(qu, lem->start))
		|| !(hm_insert(black, lem->end->name, lem->end->name)))
		ft_error("Allocation error\n", -1);
	while (!qu_is_empty(qu))
		if (!bfs_rec((t_fck)
				{qu_pop_tail(qu), black, qu, &asc_level, &get_out_first}))
			ft_error("Allocation error\n", -1);
	hm_free(black, NULL, NULL);
	qu_free(qu);
	lem->end->asc_level = INT_MAX;
}

void			lmt_bfs_desc(t_lemin *lem)
{
	t_hm		*black;
	t_qu		*qu;

	lem->end->desc_level = 0;
	if (!(qu = qu_new())
		|| !(black = hm_new(&ft_str_hash, &ft_strequ))
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
