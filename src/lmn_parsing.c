/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lmn_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:18:50 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/12 15:57:53 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_room		*lmn_check_status(t_lemin *lem, t_room *room, char **line)
{
	if (!strcmp(*line, END))
	{
		if (lem->end || !itr_has_more(lem->filtred))
			return (NULL);
		else
		{
			*line = itr_next(lem->filtred);
			room->required = 1;
			lem->end = room;
			return (lmn_check_status(lem, room, line));
		}
	}
	else if (!ft_strcmp(*line, START))
	{
		if (lem->start || !itr_has_more(lem->filtred))
			return (NULL);
		else
		{
			*line = itr_next(lem->filtred);
			room->required = 1;
			lem->start = room;
			return (lmn_check_status(lem, room, line));
		}
	}
	return (room);
}

void				parse_rooms(t_lemin *lem)
{
	t_hm			*cords;
	char			*line;
	t_room			*new;

	cords = hm_new(&ft_str_hash, (t_fequal) & ft_strequ);
	while (itr_has_more(lem->filtred) &&
			!ft_strchr(lem->filtred->cur_node->data, '-'))
	{
		line = itr_next(lem->filtred);
		if (line[0] == 'L'
			|| !(new = ft_memalloc(sizeof(t_room)))
			|| !lmn_check_status(lem, new, &line)
			|| hm_lookup(cords, ft_strchr(line, ' '))
			|| !(new = lmn_init_room(new, ft_strsplit(line, ' '))))
			ft_error("Error", -1);
		hm_insert(cords, ft_strchr(line, ' '), ft_strchr(line, ' '));
		if (hm_lookup(lem->rooms, new->name)
			||!hm_insert(lem->rooms, new->name, new))
			ft_error("Error", -1);
	}
	if (!itr_has_more(lem->filtred))
		ft_error("Error", -1);
	hm_free(cords, NULL, NULL);
}

void				parse_links(t_lemin *lem)
{
	char			*line;
	char			**linked;
	t_room			*left;
	t_room			*right;

	while ((line = itr_next(lem->filtred)) && ft_cntwords(line, '-'))
	{
		if (!(linked = ft_strsplit(line, '-')) || !*linked || !*(linked + 1))
			ft_error("Error", -1);
		if (!(left = hm_lookup(lem->rooms, linked[0])) ||
			!(right = hm_lookup(lem->rooms, linked[1])) ||
			lst_contains(left->out, (t_fequal) & room_equals, right) ||
			lst_contains(right->out, (t_fequal) & room_equals, left))
			ft_error("Error", -1);
		ft_freematr(linked);
		lst_append(right->out, left);
		lst_append(left->out, right);
		lst_append(right->in, left);
		lst_append(left->in, right);
	}
}

int					parse_ants_amount(t_lemin *lem)
{
	char			*str;

	str = itr_next(lem->filtred);
	lem->amount = str && str[0] != '-' ? ft_atoi(str) : -1;
	if (lem->amount <= 0 || !ft_atoi_check(lem->amount, str))
		ft_error("Error", -1);
	return (lem->amount);
}
