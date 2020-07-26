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

void			bfs(t_lemin *lem)
{
	t_hash_map	*black;
//	t_hash_map	*green;
	t_qu		*qu;

	if (!(qu = queue_new()) ||
		!(black = hm_new(&ft_str_hash, &string_equal)) ||
		!(queue_push_head(qu, lem->start)) ||
		!(hm_insert(black, lem->end->name, lem->end)))
		ft_error("Allocation error\n", -1);
	while (!queue_is_empty(qu))
		if (!bfs_rec((t_fck){queue_pop_tail(qu), black, qu, &asc_level, lem}))
			ft_error("Allocation error\n", -1);
	hm_clear(black);
	if (!hm_init(black, black->hash_func, black->equal_func) ||
			!(queue_push_head(qu, lem->end)) ||
			!(hm_insert(black, lem->start->name, lem->start)))
		ft_error("Allocation error\n", -1);
	while (!queue_is_empty(qu))
		if (!bfs_rec((t_fck){queue_pop_tail(qu), black, qu, &desc_level, lem}))
			ft_error("Allocation error\n", -1);


//	hm_free(green);
	queue_free(qu);
}
