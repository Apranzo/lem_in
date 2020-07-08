//
// Created by Celeste Shinohara on 7/5/20.
//

#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

#include "libft/includes/libft.h"

typedef struct		s_room
{
	char			*name;
	t_alist 		in;
	t_alist 		out;
	int				level;
}					t_room;

typedef struct		s_lemin
{
	t_alist 		raw;
	unsigned 		ants;
	t_hash_map 		rooms;
	t_room			*start;
	t_room			*end;
}					t_lemin;

void				bfs(t_lemin *lem)
size_t 				room_equals(pointer room1, pointer room2);
int 				room_free(pointer room);

#endif
