#include "includes/lem_in.h"

static int 		bfs_rec(t_room *room, t_hash_map black, t_qu *qu)
{
	size_t 			i;
	t_room			**rooms

	i = 0;
	rooms = room->out.data;
	if (!hash_map_insert(black, room->name, room))
		return (0);
	while (room->out.data[i])
	{
		if (!hash_map_lookup(black, rooms[i]->name) &&
			!queue_contains(qu, rooms[i]))
		{
			rooms[i]->level = room->level + 1;
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
			!(black = hash_map_new(&ft_hash, &room_equals)) ||
//			!(green = hash_map_new(&ft_hash, &room_equals)) ||
			!(queue_push_head(qu, lem->start)) ||
			!(hash_map_insert(black,lem->start->name, lem->start)))
		ft_error("Allocation error\n")
	while (!queue_is_empty(qu))
		if (!bfs_rec(queue_pop_tail(qu), black, qu))
			ft_error("Allocation error\n")
	hash_map_free(black);
//	hash_map_free(green);
	queue_free(qu);

}
