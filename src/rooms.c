#include "includes/lem_in.h"

int				room_equals(t_room *room1, t_room *room2)
{
	return (ft_str_hash(room1->name) == ft_str_hash(room2->name) &&
			ft_strequ(room1->name, room2->name));
}

t_node 			*get_out_first(t_room *room)
{
	return (room->out->first);
}

t_node 			*get_in_first(t_room *room)
{
	return (room->in->first);
}

int 			room_free(pointer data)
{
	t_room		*room;

	room = data;
	lst_free(room->in, NULL);
	lst_free(room->out, NULL);
	free(room->name);
	free(room);
	return (1);
}

t_room				*lmn_init_room(t_room *new, char **room)
{
	if (!new || !room ||
		!room[0] || !room[1] || !room[2] ||
		!(new->out = lst_new()) ||
		!(new->in = lst_new()))
		return (NULL);
	new->name = strdup(room[0]);
	new->cords.x = ft_atoi(room[1]);
	new->cords.y = ft_atoi(room[2]);
	if (!ft_atoi_check(new->cords.x, room[1])
		|| !ft_atoi_check(new->cords.y, room[2]))
		return (NULL);
	new->asc_level = -1;
	new->desc_level = -1;
	ft_freematr(room);
	return (new);
}