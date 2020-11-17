/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:05 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/17 20:13:37 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			print_input(const t_lemin *lem)
{
	t_itr		*itr;

	itr = lst_itr_load(lem->raw, NULL, NULL);
	while (itr_has_more(itr))
		ft_printf("%s\n", itr_next(itr));
	itr_free(itr);
}

void			print_res(t_lemin *lem)
{
	t_itr		*itr;
	t_str_bld	*bld;
	char		*output;

	lmn_prepare_paths(lem);
	itr = lst_itr_load(lem->ants, NULL, NULL);
	if (!(bld = sb_create("\n")) || (!bld->len))
		ft_error("Error", -1);
	lmn_produce_output(lem, itr, bld);
	if (!(output = sb_concat(bld)))
		ft_error("Error", -1);
//	write(1, output, bld->len);
	free(output);
	sb_free(bld);
	itr_free(itr);
}

void			print_best(t_lemin *lem)
{
	t_lst			*paths;
	t_pths 			*pth;
	t_node			*pnode;
	t_node			*node;
	t_pths 			*best;
	t_itr			*itr;
	char			*output;

	best = NULL;
	paths = lem->paths;
	pnode = paths->first;
	while (pnode)
	{
		pth = pnode->data;
		best = !best || pth->len < best->len ? pth : best;
		pnode = pnode->next;
	}
	ft_printf("\n%d\n%s", best->len, best->output);

}

void			lmn_reset(t_lemin *lem)
{
	t_itr			*itr;
	t_lst			*lst;
	t_room			*room;
	t_ant			*ant;


	lem->finished = 0;
	lst = hm_lst(lem->rooms, NULL);
	itr = lst_itr_load(lst, NULL, NULL);
	while (itr_has_more(itr))
	{
		room = itr_next(itr);
		room->ant = NULL;
	}
	itr = lst_itr_load(lem->ants, itr, NULL);
	while (itr_has_more(itr))
	{
		ant = itr_next(itr);
		ant->finished = 0;
		ant->room = NULL;
		ant->started = 0;
	}
	qu_clear(lem->qu);
	if (!(lem->qu = qu_by_lst(lem->ants)))
		ft_error("Error", -1);
	itr_free(itr);
}

void			countres(t_lemin *lem)
{
	t_lst			*paths;
	t_pths 			*pth;
	t_node			*pnode;
	t_node			*node;
	int				printed;
	t_itr			*itr;

	paths = lem->paths;
	pnode = paths->first;
	create_ants(lem);
	while (pnode)
	{
		pth = pnode->data;
		printed = 0;
		lmn_reset(lem);
		itr = lst_itr_load(lem->ants, NULL, NULL);
		t_str_bld	*bld;
		if (!(bld = sb_create("\n")) || (!bld->len))
			ft_error("Error", -1);
		while (lem->finished < lem->amount)
		{
			node = pth->paths->first;
			while (node)
			{
				pass_ants(node->data, lem);
				node = node->next;
			}
			printed = prod_line(lem, itr, bld, printed);
		}

		if (!(pth->output = sb_concat(bld)))
			ft_error("Error", -1);
		pth->len = ft_cntwords(pth->output, '\n');
		pnode = pnode->next;
	}
	print_best(lem);
}
