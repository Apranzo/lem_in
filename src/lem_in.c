/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:16:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/11 12:55:23 by cshinoha         ###   ########.fr       */
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
	lmn_del_output_forks(lst);
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
	delete_unnecerarry(lemin);
	find_path(lemin);
	print_input(lemin);
	print_res(lemin);
	free_lemin(lemin);
}
