/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:16:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/17 20:15:38 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/lem_in.h"

static int			comp_bfs_asc(t_room *left, t_room *right)
{
	if (left->asc_level > right->asc_level)
		return (1);
	else if (left->asc_level < right->asc_level)
		return (-1);
	return (0);
}

static int			comp_bfs_desc(t_room *left, t_room *right)
{
	if (left->asc_level > right->asc_level)
		return (-1);
	else if (left->asc_level < right->asc_level)
		return (1);
	return (0);
}

static	void 		pr(t_lemin *lem)
{
	t_lst			*lst;
	t_itr			*itr;
	t_room			*room;

	lst = hm_lst(lem->rooms, NULL);
	lst_sort(lst, (t_fcompare) & comp_bfs_asc);
	itr = lst_itr_load(lst, NULL, NULL);

	ft_printf("start: %s--->end: %s\n", lem->start->name, lem->end->name);
	while (itr_has_more(itr))
	{
		room = itr_next(itr);
		ft_printf("name %s\tasc: %d\tdes: %d\n", room->name, room->asc_level, room->desc_level);
	}
}

static t_room 		*mindesc(t_room *room, t_lemin *lem)
{
	t_room 			*less;
	t_room 			*edge;
	t_node			*node;

	less = NULL;
	node = room->out->first;
	while (node)
	{
		edge = node->data;
		if (!hm_lookup(lem->inpath, edge->name))
		{
			if (!less)
				less = edge;
			else
			{
				less = less->desc_level > edge->desc_level ?
					   edge :
					   less;
			}
		}
		node = node->next;
	}
	return (less);
}

static t_lst		*shortest(t_lemin *lem)
{
	t_lst			*pth;
	t_room			*room;

	room = lem->start;
	pth = lst_new();
	while ((room = mindesc(room, lem)))
	{
		if (lst_contains(pth, (t_fequal) & room_equals, room))
			break ;
		lst_append(pth, room);
		if (room == lem->end)
			return (pth);
		else
			if (!(hm_insert(lem->inpath, room->name, room->name)))
				ft_error("main alloc error", -1);

	}
	lst_clear(pth, NULL);
	return (NULL);
}

t_pths				*lmn_find_path(t_lemin *lem)
{
	t_node *node;
	t_pths *pths;
	t_pth *path;

	node = lem->start->out->first;
	pths = ft_memalloc(sizeof(t_pths));
	pths->paths = lst_new();
	while (node)
	{
		path = ft_memalloc(sizeof(t_pth));
		if (!(path->rooms = shortest(lem))) {
			free(path);
		}
		else
			lst_append(pths->paths, path);
		node = node->next;
	}
	if (!pths->paths->length)
		return (NULL);
	return (pths);
}

void				lmn_brut(t_lemin *lem)
{
	t_pth 			*shrt;
	t_itr			*sitr;
	t_itr			*pitr;
	t_room 			*name;
	t_pths			*pths;
	int i = 0;

	pths = lmn_find_path(lem);
	lst_append(lem->paths, pths);
	pitr = lst_itr_load(pths->paths, NULL, NULL);
//	lst_sort(pths->paths, (t_fcompare) & cmpr_lst_ln);
	while (itr_has_more(pitr) && i < 100)
	{
		shrt = itr_next(pitr);
		sitr = lst_itr_load(shrt->rooms, NULL, NULL);
		while (itr_has_more(sitr) && i++ < 100)
		{
			hm_clear(lem->inpath);
			name = itr_next(sitr);
			hm_insert(lem->inpath, name->name, name->name);
			if((pths = lmn_find_path(lem)))
				lst_append(lem->paths, pths);
		}
	}
	if (!lem->paths->length)
		ft_error("Error", -1);
}

//void				delete_unnecerarry(t_lemin *lem)
//{
//	t_lst			*lst;
//
//	lst = hm_lst(lem->rooms, NULL);
//	lst_sort(lst, (t_fcompare) & comp_bfs_asc);
//	lmn_check_unuses(lst);
////	lmn_alight(lst);
////	lmn_del_dead_end(lst);
////	lmn_del_input_forks(lst);
////	lmt_bfs_desc(lem);
////	lst_sort(lst, (t_fcompare) & comp_bfs_desc);
////	lmn_del_output_forks(lst);
//	lst_free(lst, NULL);
//}

static void			free_lemin(t_lemin *lemin)
{
	lst_free(lemin->raw, free);
	itr_free(lemin->filtred);
	lst_free(lemin->paths, (t_ffree) & free_path);
	lst_free(lemin->ants, free);
	qu_free(lemin->qu);
	hm_free(lemin->rooms, NULL, (t_ffree) & room_free);
	free(lemin);
}

int					main(void)
{
	static t_lemin	*lemin;

	freopen("map", "r", stdin);


	if (!(lemin = ft_memalloc(sizeof(t_lemin))) ||
			!(lemin->raw = lst_new()))
		ft_error("main alloc error", -1);
	read_intput(STDIN_FILENO, lemin);
	parse_ants_amount(lemin);
	lemin->rooms = hm_new(&ft_str_hash, (t_fequal) & ft_strequ);
	lemin->inpath = hm_new(&ft_str_hash, (t_fequal) & ft_strequ);
	lemin->paths = lst_new();
	parse_rooms(lemin);
	parse_links(lemin);
	if (!lemin->start || !lemin->end || !lemin->start->out)
		ft_error("Error", -1);
//	create_ants(lemin);
//	lmn_bfs_asc(lemin);
//	pr(lemin);
//	delete_unnecerarry(lemin);
//	lst = hm_lst(lemin->rooms, NULL);
//	lst_sort(lst, (t_fcompare) & comp_bfs_asc);
//	lmn_check_unuses(lst);
//	lmn_alight(lst);
//	lmn_del_dead_end(lst);
	lmt_bfs_desc(lemin);
//	pr(lemin);
	lmn_brut(lemin);
	lmn_prepare_paths(lemin);
//	lmn_find_path(lemin);
//	print_input(lemin);
	countres(lemin);
//	print_res(lemin);
	free_lemin(lemin);
}
