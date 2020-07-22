#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/includes/libft.h"

typedef struct		s_room
{
	char			*name;
	t_lst 			*links;
	size_t 			ant;
	int				asc_level;
	int				desc_level;
	int				in;
	int				required;
//	int				start;
//	int				end;
	t_xy			cords;
}					t_room;

typedef struct		s_lemin
{
	t_lst 			*raw;
	t_itr 			*filtred;
	t_lst 			*paths;
	size_t			ants;
	t_hash_map 		*rooms;
	t_room			*start;
	t_room			*end;
}					t_lemin;

void				bfs(t_lemin *lem);
int					room_equals(pointer room1, pointer room2);
int 				room_free(pointer room);

#endif
