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
