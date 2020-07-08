#include "includes/lem_in.h"

size_t 			room_equals(pointer room1, pointer room2)
{
	t_room		*r1;
	t_room		*r2;
	return (ft_hash(room1) == ft_hash(room2) &&
			string_equal((t_room*)room1)->name, ((t_room*)room2)->name));
}

int 			room_free(pointer room)
{
	free((t_room*)room)->name)
	free(room);
}
