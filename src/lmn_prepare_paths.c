/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:22:49 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/15 18:45:19 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			cmpr_lst_ln(t_pth *lft, t_pth *rght)
{
	return (lft->rooms->length - rght->rooms->length);
}

int			cmpr_lst_ln_desc(t_pth *lft, t_pth *rght)
{
	return (cmpr_lst_ln(lft, rght) * -1);
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
	t_lst			*paths;
	t_pths 			*pth;
	t_node			*node;

	paths = lem->paths;
	node = paths->first;
	while (node)
	{
		pth = node->data;
		lst_sort(pth->paths, (t_fcompare) & cmpr_lst_ln);
		lst_foreach(pth->paths, (t_fmap) & sum_prev_ln);
		lst_sort(pth->paths, (t_fcompare) & cmpr_lst_ln_desc);
		node = node->next;
	}
}
