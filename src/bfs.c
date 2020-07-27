#include "includes/lem_in.h"

struct s_fuck_the_system
{
	t_room			*room;
	t_hash_map		*black;
	t_qu			*qu;
	void			(*f_level)(t_room *child, t_room *parent);
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
						parent->desc_level - 1;
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
	if (!node || room->required)
		return ;
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

static int 			bfs_rec(t_fck fck)
{
	t_node 			*node;

	node = fck.room->out->first;
	if (!hm_insert(fck.black, fck.room->name, fck.room))
		return (0);
	while (node)
	{
		if (!hm_lookup(fck.black, ((t_room *)node->data)->name) &&
			!queue_contains(fck.qu, node->data))
		{
			fck.f_level(node->data, fck.room);
			if (!queue_push_head(fck.qu, node->data))
				return (0);
		}
		node = node->next;
	}
	return (1);
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
		!(qu = queue_new()) || !(queue_push_head(qu, start)) ||
		(end && !hm_insert(black, end->name, end->name)))
			return (NULL);
	itr_clear(itr);
	while ((room = queue_pop_tail(qu)) && (node = get_first(room)))
	{
		if (!hm_insert(black, room->name, room))
			ft_error("Allocation error\n", -1);
		while (node)
		{
			if (!hm_lookup(black, ((t_room *)node->data)->name) &&
				!queue_contains(qu, node->data))
				if (!ft_node_append(&itr->_cur_node, node->data) ||
						!queue_push_head(qu, node->data))
					ft_error("Allocation error\n", -1);
			node = node->next;
		}
	}
	itr->_start_node = itr->_cur_node;
	return (itr);
}

void			bfs_asc_level(t_lemin *lem)
{
	t_itr		*itr;

	if (!(itr = bfs_trip(lem->start, lem->end, NULL, &get_out_first)))
		ft_error("Allocation error\n", -1);
	itr_foreach(itr, (void (*)(pointer)) &calc_asc);
	itr_free(itr);
}

void			bfs_desc_level(t_lemin *lem)
{
	t_itr		*itr;

//	lem->end->desc_level = INT_MAX;
	if (!(itr = bfs_trip(lem->end, NULL, NULL, &get_in_first)))
		ft_error("Allocation error\n", -1);
	pr_iter(itr);
	itr_foreach(itr, (void (*)(pointer)) &calc_desc);
	itr_free(itr);
}
