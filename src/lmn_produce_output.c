/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_produce_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:30:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 15:04:18 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			move(t_lst *lst)
{
	t_node		*node;
	t_ant		*prev;

	node = lst->last;
	prev = node->prev ? ((t_room*)node->prev->data)->ant : NULL;
	if (node->prev && prev)
	{
		((t_room*)node->data)->ant = prev;
		prev->room = node->data;
	}
	node = node->prev;
	while (node && node->prev)
	{
		prev = ((t_room*)node->prev->data)->ant;
		((t_room*)node->data)->ant = prev;
		if (prev)
			prev->room = node->data;
		((t_room*)node->data)->ant = ((t_room*)node->prev->data)->ant;
		node = node->prev;
	}
	if (node)
		((t_room*)node->data)->ant = NULL;
}

int				prod_line(t_lemin *lem, t_itr *itr,
							t_str_bld *bld, int printed)
{
	t_ant		*ant;

	while (itr_has_more(itr))
	{
		ant = itr_next(itr);
		if (ant->started && !ant->finished)
		{
			if (lem->opt && lem->opt->color && ant->room == lem->end)
				ft_sbprintf(bld, ANSI_COLOR_RED);
			if (lem->opt && lem->opt->color)
				ft_sbprintf(bld,"L%zu-%s\x1B[0m ", ant->number, ant->room->name);
			else
				ft_sbprintf(bld,"L%zu-%s ", ant->number, ant->room->name);
		}
		if (!ant->finished && ant->room == lem->end)
			lem->finished += (ant->finished = 1);
	}
	printed++;
	sb_repl_by_ind(bld, bld->len - 1, '\n');
	itr_reset(itr);
	return (printed);
}

int				pass_ants(t_pth *pth, t_lemin *lemin)
{
	t_room		*room;

	move(pth->rooms);
	if (!qu_is_empty(lemin->qu)
		&& lemin->amount - ((t_ant*)qu_peek_head(lemin->qu))->number + 1
			>= pth->cost)
	{
		room = pth->rooms->first->data;
		room->ant = qu_pop_head(lemin->qu);
		room->ant->room = pth->rooms->first->data;
		room->ant->started = 1;
	}
	return (1);
}
