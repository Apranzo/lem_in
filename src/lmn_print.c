/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:05 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 18:42:38 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		move(t_lst *lst)
{
	t_node		*node;
	t_ant		*prev;

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

static int		pass_ants(t_pth *pth, t_lemin *lemin)
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

void			print_input(const t_lemin *lem)
{
	t_itr		*itr;

	itr = lst_itr_load(lem->raw, NULL, NULL);
	while (itr_has_more(itr))
		ft_printf("%s\n", itr_next(itr));
}

int				produce_line(t_lemin *lem, t_itr *itr, char **line, int printed)
{
	t_ant		*ant;

	while (itr_has_more(itr))
	{
		ant = itr_next(itr);
		if (ant->started && !ant->finished)
			printed += ft_sprintf(line,
					"L%zu-%s ", ant->number, ant->room->name);
		if (!ant->finished && ant->room == lem->end)
			lem->finished += (ant->finished = 1);
	}
	if ((*line)[printed] == ' ')
		(*line)[printed] = '\n';
	itr_reset(itr);
	return (printed);
}

void			print_res(t_lemin *lem)
{
	t_node		*node;
	t_itr		*itr;
	char		*line;
	int			printed;

	print_input(lem);
	prepare_paths(lem);
	itr = lst_itr_load(lem->ants, NULL, NULL);
	printed = 0;
	line = ft_strdup("\n");
	while (lem->finished < lem->amount)
	{
		node = lem->paths->first;
		while (node)
		{
			pass_ants(node->data, lem);
			node = node->next;
		}
		printed = produce_line(lem, itr, &line, printed);
	}
	ft_putstr(line);
	free(line);
	itr_free(itr);
}
