/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:16:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/18 17:16:13 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void			free_lemin(t_lemin *lemin)
{
	lst_free(lemin->raw, free);
	itr_free(lemin->filtred);
	lst_free(lemin->paths, (t_ffree) & free_pathes_wrapper);
	lst_free(lemin->ants, free);
	qu_free(lemin->qu);
	hm_free(lemin->rooms, NULL, (t_ffree) & room_free);
	hm_free(lemin->inpath, NULL, NULL);
	free(lemin);
}

int					main(void)
{
	static t_lemin	*lemin;

	if (!(lemin = ft_memalloc(sizeof(t_lemin)))
		|| !(lemin->raw = lst_new())
		|| !(lemin->rooms = hm_new(&ft_str_hash, (t_fequal) & ft_strequ))
		|| !(lemin->inpath = hm_new(&ft_str_hash, (t_fequal) & ft_strequ))
		|| !(lemin->paths = lst_new()))
		ft_error("main alloc error", -1);
	read_intput(STDIN_FILENO, lemin);
	parse_ants_amount(lemin);
	parse_rooms(lemin);
	parse_links(lemin);
	if (!lemin->start || !lemin->end || !lemin->start->out)
		ft_error("Error", -1);
	create_ants(lemin);
	lmt_bfs_desc(lemin);
	lmn_brut(lemin);
	lmn_prepare_paths(lemin);
	print_input(lemin);
	countres(lemin);
	free_lemin(lemin);
}
