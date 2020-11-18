/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   et_tu_brute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:00:53 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/18 17:42:32 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_pths		*lmn_find_path(t_lemin *lem)
{
	t_node			*node;
	t_pths			*pths;
	t_pth			*path;

	node = lem->start->out->first;
	pths = ft_memalloc(sizeof(t_pths));
	pths->paths = lst_new();
	while (node)
	{
		path = ft_memalloc(sizeof(t_pth));
		if (!(path->rooms = shortest(lem)))
			free(path);
		else
			lst_append(pths->paths, path);
		node = node->next;
	}
	if (!pths->paths || !pths->paths->length)
	{
		free_pathes_wrapper(pths);
		return (NULL);
	}
	return (pths);
}

static void			lmn_inner_brut(t_lemin *lem,
									t_itr *pitr, t_pths *pths, t_itr **sitr)
{
	t_pth			*shrt;
	t_room			*room;

	shrt = itr_next(pitr);
	*sitr = lst_itr_load(shrt->rooms, *sitr, NULL);
	while (itr_has_more(*sitr) && lem->count++ < NOTHING_ELSE)
	{
		hm_clear(lem->inpath);
		room = itr_next(*sitr);
		hm_insert(lem->inpath, room->name, room->name);
		if ((pths = lmn_find_path(lem)))
			lst_append(lem->paths, pths);
	}
	itr_reset(*sitr);
}

static void			ants_reset(t_lemin *lem)
{
	t_ant			*ant;
	t_itr			*itr;

	itr = lst_itr_load(lem->ants, NULL, NULL);
	while (itr_has_more(itr))
	{
		ant = itr_next(itr);
		ant->finished = 0;
		ant->room = NULL;
		ant->started = 0;
	}
	qu_free(lem->qu);
	if (!(lem->qu = qu_by_lst(lem->ants)))
		ft_error("Error", -1);
	itr_free(itr);
}

void				lmn_reset(t_lemin *lem)
{
	t_itr			*itr;
	t_lst			*lst;
	t_room			*room;

	lem->finished = 0;
	lst = hm_lst(lem->rooms, NULL);
	itr = lst_itr_load(lst, NULL, NULL);
	while (itr_has_more(itr))
	{
		room = itr_next(itr);
		room->ant = NULL;
	}
	ants_reset(lem);
	lst_free(lst, NULL);
	itr_free(itr);
}

void				lmn_brut(t_lemin *lem)
{
	t_itr			*sitr;
	t_itr			*pitr;
	t_pths			*pths;

	if (!(pths = lmn_find_path(lem)))
		ft_error("Error", -1);
	lst_append(lem->paths, pths);
	pitr = lst_itr_load(pths->paths, NULL, NULL);
	sitr = NULL;
	while (itr_has_more(pitr) && lem->count < NOTHING_ELSE)
		lmn_inner_brut(lem, pitr, pths, &sitr);
	itr_free(pitr);
	itr_free(sitr);
	if (!lem->paths->length)
		ft_error("Error", -1);
}
