/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:22:49 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/09 17:39:07 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int			cmpr_lst_ln(t_pth *lft, t_pth *rght)
{
	return (lft->rooms->length - rght->rooms->length);
}

static void			sum_prev_ln(t_node *node)
{
	t_pth			*pth;

	pth = node->data;
	pth->cost = 0;
	while (node->prev)
	{
		pth->cost += pth->rooms->length
				- ((t_pth *)node->prev->data)->rooms->length;
		node = node->prev;
	}
}

void				lmn_prepare_paths(const t_lemin *lem)
{
	lst_sort(lem->paths, (t_fcompare) & cmpr_lst_ln);
	lst_foreach(lem->paths, (t_fmap) & sum_prev_ln);
}
