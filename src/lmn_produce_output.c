/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_produce_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:30:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/15 17:25:10 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		move(t_lst *lst)
{
	t_node		*node;
	t_ant		*prev;

	node = lst->last;
	prev = ((t_edge *)node->prev->data)->dts->ant;
	if (node->prev && prev)
	{
		((t_edge *)node->data)->dts->ant = prev;
		prev->room = ((t_edge *)node->data)->dts;;
	}
	node = node->prev;
	while (node && node->prev)
	{
		prev = ((t_edge *)node->prev->data)->dts->ant;
		((t_edge *)node->data)->dts->ant = prev;
		if (prev)
			prev->room = ((t_edge *)node->data)->dts;
		((t_edge *)node->data)->dts->ant = ((t_edge *)node->prev->data)->dts->ant;
		node = node->prev;
	}
	if (node)
		((t_edge *)node->data)->dts->ant = NULL;
}

int				prod_line(t_lemin *lem, t_itr *itr,
							t_str_bld *bld, int printed)
{
	t_ant		*ant;

	while (itr_has_more(itr))
	{
		ant = itr_next(itr);
		if (ant->started && !ant->finished)
			printed += ft_sbprintf(bld,
								"L%zu-%s ", ant->number, ant->room->name);
		if (!ant->finished && ant->room == lem->end)
			lem->finished += (ant->finished = 1);
	}
	if (sb_by_ind(bld, printed) == ' ')
		sb_repl_by_ind(bld, printed, '\n');
	itr_reset(itr);
	return (printed);
}

int		pass_ants(t_pth *pth, t_lemin *lemin)
{
	t_room		*room;
	t_edge 		*ed;

	move(pth->rooms);
	if (!qu_is_empty(lemin->qu)
		&& lemin->amount - ((t_ant*)qu_peek_head(lemin->qu))->number + 1
			>= pth->cost)
	{
		ed = pth->rooms->first->data;
		room = ed->dts;
		room->ant = qu_pop_head(lemin->qu);
		room->ant->room = ((t_edge*)pth->rooms->first->data)->dts;
		room->ant->started = 1;
	}
	return (1);
}

void			lmn_produce_output(t_lemin *lem, t_itr *itr, t_str_bld *bld)
{
	t_node		*node;
	int			printed;

	printed = 0;
	while (lem->finished < lem->amount)
	{
		node = lem->paths->first;
		while (node)
		{
			pass_ants(node->data, lem);
			node = node->next;
		}
		printed = prod_line(lem, itr, bld, printed);
	}
}
