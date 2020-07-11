#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/includes/libft.h"

typedef struct		s_room
{
	char			*name;
	t_alst 		links;
	int				level;
}					t_room;

typedef struct		s_lemin
{
	t_alst 			raw;
	size_t			ants;
	t_hash_map 		rooms;
	t_room			*start;
	t_room			*end;
}					t_lemin;

void				bfs(t_lemin *lem);
size_t 				room_equals(pointer room1, pointer room2);
int 				room_free(pointer room);

#endif
