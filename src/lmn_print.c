/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:05 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 20:37:21 by cshinoha         ###   ########.fr       */
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

static void			move(t_lst *lst)
{
	t_node			*node;
	t_ant			*prev;

	node = lst->last;
	prev = ((t_room*)node->prev->data)->ant;
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

static int			pass_ants(t_pth *pth, t_lemin *lemin)
{
	t_room			*room;

	move(pth->rooms);
	if (!qu_is_empty(lemin->qu)
		&& lemin->amount - ((t_ant*)qu_peek_head(lemin->qu))->number + 1
		> pth->cost)
	{
		room = pth->rooms->first->data;
		room->ant = qu_pop_head(lemin->qu);
		room->ant->room = pth->rooms->first->data;
		room->ant->started = 1;
	}
	return (1);
}

void				print_res(t_lemin *lem)
{
	t_node			*node;
	t_pth			*pth;
	t_itr			*itr;
	t_ant			*ant;
	char			*line;
	int				printed;

	line = NULL;
	itr = lst_itr_load(lem->raw, NULL, NULL);
	while (itr_has_more(itr))
		ft_printf("%s\n", itr_next(itr));
	ft_printf("\n");
	itr_clear(itr);
	lst_sort(lem->paths, (f_compare)&cmpr_lst_ln);
	lst_foreach(lem->paths, (f_map)&sum_prev_ln);
	lst_itr_load(lem->ants, itr, NULL);
	printed = 0;
	while (lem->finished < lem->amount)
	{
		node = lem->paths->first;
		while (node)
		{
			pth = node->data;
			pass_ants(pth, lem);
			node = node->next;
		}
		while (itr_has_more(itr))
		{
			ant = itr_next(itr);
			if (ant->started && !ant->finished)
				printed += ft_sprintf(&line,
						"L%zu-%s ", ant->number, ant->room->name);
			if (!ant->finished && ant->room == lem->end)
				lem->finished += (ant->finished = 1);
		}
		if (line[printed - 1] == ' ')
			line[printed - 1] = '\n';
		itr_reset(itr);
	}
	ft_putstr(line);
	free(line);
	itr_free(itr);
}
