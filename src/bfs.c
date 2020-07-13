#include "includes/lem_in.h"

static void		asc_level(t_room *child, t_room *parent)
{
	child->asc_level = child->asc_level > 0 &&
						child->asc_level < parent->asc_level + 1 ?
						child->asc_level :
					   parent->asc_level + 1;
}

static void		desc_level(t_room *child, t_room *parent)
{
	child->asc_level = child->desc_level > 0 &&
						child->desc_level < parent->desc_level + 1 ?
						child->desc_level :
						parent->desc_level + 1;
}

static int 		bfs_rec(t_room *room, t_hash_map *black, t_qu *qu,
							void (*f_level)(t_room *child, t_room *parent))
{
	size_t 			i;
	t_room			**rooms;
	i = 0;
	rooms = (t_room **) room->links.data;
	if (!hm_insert(black, room->name, room))
		return (0);
	while (i < room->links.length)
	{
		if (!hm_lookup(black, rooms[i]->name) &&
			!queue_contains(qu, rooms[i]))
		{
			f_level(rooms[i], room);
			if (!queue_push_head(qu, rooms[i]))
				return (0);
		}
		i++;
	}
	return (1);
}

void			bfs(t_lemin *lem)
{
	t_hash_map	*black;
//	t_hash_map	*green;
	t_qu		*qu;

	if (	!(qu = queue_new()) ||
			!(black = hm_new(&ft_hash, &room_equals)) ||
			!(queue_push_head(qu, lem->start)) ||
			!(hm_insert(black, lem->start->name, lem->start)))
		ft_error("Allocation error\n", -1);
	while (!queue_is_empty(qu))
		if (!bfs_rec(queue_pop_tail(qu), black, qu, &asc_level))
			ft_error("Allocation error\n", -1);
	hm_clear(black);
	if (	!(hm_init(black, black->hash_func, black->equal_func) ||
			!(queue_push_head(qu, lem->end)) ||
			!(hm_insert(black, lem->end->name, lem->end))))
		ft_error("Allocation error\n", -1);
	while (!queue_is_empty(qu))
		if (!bfs_rec(queue_pop_tail(qu), black, qu, &desc_level))
			ft_error("Allocation error\n", -1);


//	hm_free(green);
	queue_free(qu);
}
