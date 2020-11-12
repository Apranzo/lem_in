/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:16:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/12 15:30:45 by cshinoha         ###   ########.fr       */
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

//static t_room 		*mincap(t_room *par)
//{
//	t_lst			*out;
//	t_node			*node;
//	t_room			*room;
//	t_room			*min;
//
//	min = NULL;
//	out = par->out;
//	node = out->first;
//	while (node)
//	{
//		room = node->data;
//		if (!min || min->cin > room->cin)
//			min = room;
//	}
//	return (room);
//}

//static int 			fillcap(t_lemin *lem)
//{
//	t_node			*node;
//	t_lst			*br;
//	t_pth			*path;
//	t_room			*room;
//
//	node = lem->start->out->first;
//	lem->paths = lst_new();
//	while (node)
//	{
//		room = node->data;
//
//		br = lst_new();
//		path = ft_memalloc(sizeof(t_pth));
//		path->rooms = br;
//		lst_append(br, node->data);
//		if (!build_path(lem, br))
//			free_path(path);
//		else
//			lst_append(lem->paths, path);
//		node = node->next;
//	}
//
//}

void				delete_unnecerarry(t_lemin *lem)
{
	t_lst			*lst;

	lst = hm_lst(lem->rooms, NULL);
	lst_sort(lst, (t_fcompare) & comp_bfs_asc);
	lmn_check_unuses(lst);
	lmn_alight(lst);
	lmn_del_dead_end(lst);
	lmn_del_input_forks(lst);
	lmt_bfs_desc(lem);
	lst_sort(lst, (t_fcompare) & comp_bfs_desc);
//	lmn_del_input_forks(lst);
	lmn_del_output_forks(lst);
//	l_check_unuses(lst);
	lst_free(lst, NULL);
}

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

static t_edge 		*mindesc(t_room *room)
{
	t_edge 			*less;
	t_edge 			*edge;
	t_node			*node;

	less = NULL;
	node = room->out->first;
	while (node)
	{
		edge = node->data;
		if (!less)
			less = edge;
		else
		{
			less = edge->dest->desc_level > 0 && edge.
				   less->dest->desc_level > edge->dest->desc_level ?
				   edge:
				   less;
		}
		node = node->next;
	}
	return (less);

}

static t_lst		*shortest(t_lemin *lem)
{
	t_lst			*pth;
	t_room 			*less;
	t_room			*room;
	t_edge 			*edge;
	t_node			*node;

	room = lem->start;
	pth = lst_new();
//	node = room->out->first;
	less = NULL;
	edge = NULL;
	while ((edge = mindesc(room)))
	{
		lst_append(pth, edge);
		if (edge->dest == lem->end)
			return (pth);
		else if (lst_contains(pth, (t_fequal) & edge_equals, edge))
			break ;
	}
	lst_clear(pth, free);
	return (NULL);
}

static void 		fill_capacity(t_lst *pth)
{
	t_node			*node;
	t_edge			*edge;

	node = pth->first;
	while (node)
	{
		edge = node->data;
		edge->cdest = 1;
		edge->csrc = -1;
		node = node->next;
	}
}

static	void 		pr(t_lemin *lem)
{

	t_lst			*pth;
	t_itr			*itr;
	t_room			*room;
	t_edge 			*edge;

	room = lem->start;

	pth = shortest(lem);

	while (room != lem->end)
	{

	}

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
	parse_rooms(lemin);
	parse_links(lemin);
	if (!lemin->start || !lemin->end || !lemin->start->out)
		ft_error("Error", -1);
	create_ants(lemin);
	lmn_bfs_asc(lemin);
	lmt_bfs_desc(lemin);
	pr(lemin);
	shortest(lemin);
	delete_unnecerarry(lemin);
	find_path(lemin);
	print_input(lemin);
	print_res(lemin);
	free_lemin(lemin);
}
