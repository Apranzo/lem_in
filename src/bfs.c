#include "includes/lem_in.h"

struct s_fuck_the_system
{
	t_room			*room;
	t_hash_map		*black;
	t_qu			*qu;
	void			(*f_level)(t_room *child, t_room *parent);
	t_node			*(*get_first)(t_room *);
	t_lemin			*lemin;

};

typedef struct s_fuck_the_system t_fck;

static void		asc_level(t_room *child, t_room *parent)
{
	child->asc_level = child->asc_level > 0 &&
						child->asc_level < parent->asc_level + 1 ?
						child->asc_level :
					   parent->asc_level + 1;
}

static void		desc_level(t_room *child, t_room *parent)
{
	child->desc_level = child->desc_level > 0 &&
						child->desc_level < parent->desc_level + 1 ?
						child->desc_level :
						parent->desc_level + 1;
}

static	void 		calc_asc(t_room *room)
{
	t_node			*node;
	t_room			*parnt;

	node = room->in->first;
	while (node)
	{
		parnt = node->data;
		room->asc_level = room->asc_level < 0 ||
							 (parnt->asc_level >= 0 &&
							 	parnt->asc_level + 1 < room->asc_level) ?
						  parnt->asc_level + 1 : room->asc_level;
		node = node->next;
	}
}

static	void 		calc_desc(t_room *room)
{
	t_node			*node;
	t_room			*parnt;
	int				min;

	node = room->out->first;
	min = -1;
	while (node)
	{
		parnt = node->data;
		if (min < 0 || (min > parnt->desc_level && parnt->desc_level >= 0))
			min = parnt->desc_level;
//		if (parnt->desc_level >= 0)
//		room->desc_level = room->desc_level < 0 ||
//						  (parnt->desc_level >= 0 &&
//						   parnt->desc_level + 1 < room->desc_level) ?
//						  parnt->desc_level - 1 : room->desc_level;
		node = node->next;
	}
	room->desc_level = min + 1;
}

static void				pr_iter(t_itr *itr)
{
	t_node *node;

	node = itr->_cur_node;

	ft_printf("\n********************\n");
	while (node)
	{
		ft_printf("%s\n", ((t_room*)node->data)->name);
		node = node->next;
	}
	ft_printf(":::::::::::::::::::::::::::::::\n");
}

static void pr_room(const t_room *room) {
	ft_printf("NAME\t%s\nasc\t%d\ndesc\t%d\nin\t%zu\nreq\t%d\n+++++++++++++++++++\n",
		   room->name, room->asc_level, room->desc_level, room->in->length, room->required);
}

t_itr 			*bfs_trip(t_room *start, t_room *end, t_itr *itr, t_node *(*get_first)(t_room *))
{
	t_node 			*node;
	t_hash_map		*black;
	t_qu			*qu;
	t_room			*room;

	if ((!itr && !(itr = ft_memalloc(sizeof(t_itr)))) ||
		!(black = hm_new(&ft_str_hash, (f_equal) &string_equal)) ||
		!(qu = qu_new()) || !(qu_push_head(qu, start))
		|| (end && !hm_insert(black, end->name, end->name))
		)
			return (NULL);
	itr_clear(itr);
	while ((room = qu_pop_tail(qu)))
	{
		if (!hm_insert(black, room->name, room))
			ft_error("Allocation error\n", -1);
		node = get_first(room);
		while (node)
		{
			if (!hm_lookup(black, ((t_room *)node->data)->name) &&
				!qu_contains(qu, node->data))
				if (!ft_node_append(&itr->_cur_node, node->data) ||
						!qu_push_head(qu, node->data))
					ft_error("Allocation error\n", -1);
			node = node->next;
		}
	}
	itr->_start_node = itr->_cur_node;
	return (itr);
}


static int 			bfs_rec(t_fck fck)
{
	t_node 			*node;

	node = fck.get_first(fck.room);
	if (!hm_insert(fck.black, fck.room->name, fck.room))
		return (0);
	while (node)
	{
		if (!hm_lookup(fck.black, ((t_room *)node->data)->name) &&
			!qu_contains(fck.qu, node->data))
		{
			fck.f_level(node->data, fck.room);
			if (!qu_push_head(fck.qu, node->data))
				return (0);
		}
		node = node->next;
	}
	return (1);
}

void			bfs_asc_level(t_lemin *lem)
{
	t_hash_map	*black;
	t_qu		*qu;

	lem->start->asc_level = 0;
	if (!(qu = qu_new())
		|| !(black = hm_new(&ft_str_hash, &string_equal))
		|| !(qu_push_head(qu, lem->start))
		|| !(hm_insert(black, lem->end->name, lem->end->name)))
				ft_error("Allocation error\n", -1);
	while (!qu_is_empty(qu))
		if (!bfs_rec((t_fck){qu_pop_tail(qu), black, qu, &asc_level, &get_out_first, lem}))
				ft_error("Allocation error\n", -1);
	hm_free(black, NULL, NULL);
	qu_free(qu);
	lem->end->asc_level = INT_MAX;
}

void			bfs_desc_level(t_lemin *lem)
{
	t_hash_map	*black;
	t_qu		*qu;

	lem->end->desc_level = 0;
	if (!(qu = qu_new())
		|| !(black = hm_new(&ft_str_hash, &string_equal))
		|| !(qu_push_head(qu, lem->end))
		|| !(hm_insert(black, lem->start->name, lem->start)))
		ft_error("Allocation error\n", -1);
	while (!qu_is_empty(qu))
		if (!bfs_rec((t_fck){qu_pop_tail(qu), black, qu, &desc_level, &get_in_first, lem}))
			ft_error("Allocation error\n", -1);
	hm_free(black, NULL, NULL);
	qu_free(qu);
	lem->start->desc_level = INT_MAX;
}
