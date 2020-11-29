/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:05 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void			prp(t_lst *p, t_lemin *lem)
{
	t_pth			*pth;
	t_itr			*itr;
	t_itr			*eitr;
	t_room			*ed;

	itr = lst_itr_load(p, NULL, NULL);
	while (itr_has_more(itr))
	{
		pth = itr_next(itr);
		eitr = lst_itr_load(pth->rooms, NULL, NULL);
		ft_vfprintf(lem->opt->out, "len: \t%d\n", pth->rooms->length);
		while (itr_has_more(eitr))
		{
			ed = itr_next(eitr);
			ft_vfprintf(lem->opt->out, "-> %s ", ed->name);
		}
		ft_vfprintf(lem->opt->out, "\n");
		itr_reset(eitr);
	}
	ft_vfprintf(lem->opt->out, "\n");
	itr_free(itr);
	itr_free(eitr);
}

void				print_input(const t_lemin *lem)
{
	t_itr			*itr;

	if (lem->opt->req == -1)
	{
		itr = lst_itr_load(lem->raw, NULL, NULL);
		while (itr_has_more(itr))
			ft_vfprintf(lem->opt->out, "%s\n", itr_next(itr));
		ft_vfprintf(lem->opt->out, "\n");
		itr_free(itr);
	}
}

static void			print_best(t_lemin *lem)
{
	t_lst			*paths;
	t_pths			*pth;
	t_node			*pnode;
	t_pths			*best;

	best = NULL;
	paths = lem->paths;
	pnode = paths->first;
	while (pnode)
	{
		pth = pnode->data;
		best = !best || (pth->steps && pth->steps < best->steps) ? pth : best;
		pnode = pnode->next;
	}
	if (lem->opt->pth)
		prp(best->paths, lem);
	if (lem->opt->req > -1)
		ft_vfprintf(lem->opt->out
			, "lines required: %d\nlines produced: %d\ndiff: %d\n"
			, lem->opt->req, best->steps, best->steps - lem->opt->req);
	else
		write(lem->opt->out, best->output, best->len);
}

void				prod(t_lemin *lem, t_pths *pth, t_str_bld *bld, t_itr **itr)
{
	t_node			*node;

	*itr = lst_itr_load(lem->ants, *itr, NULL);
	while (lem->finished < lem->amount)
	{
		node = pth->paths->first;
		while (node)
		{
			pass_ants(node->data, lem);
			node = node->next;
		}
		pth->steps = prod_line(lem, *itr, bld, pth->steps);
	}
	if (!(pth->output = sb_concat(bld)))
		ft_error("Error", -1);
	pth->len = bld->len;
}

void				countres(t_lemin *lem)
{
	t_node			*pnode;
	t_str_bld		*bld;
	t_itr			*itr;

	itr = NULL;
	pnode = lem->paths->first;
	if (!(bld = sb_create(NULL)))
		ft_error("Error", -1);
	while (pnode)
	{
		prod(lem, pnode->data, bld, &itr);
		lmn_reset(lem);
		sb_reset(bld);
		sb_append(bld, "\n");
		itr_reset(itr);
		pnode = pnode->next;
	}
	itr_free(itr);
	sb_free(bld);
	print_best(lem);
}
