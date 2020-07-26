#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/includes/libft.h"

typedef struct		s_room
{
	char			*name;
	t_lst 			*out;
	t_lst 			*in;
	size_t 			ant;
	int				asc_level;
	int				desc_level;
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
	size_t			finished;
	t_hash_map 		*rooms;
	t_room			*start;
	t_room			*end;
}					t_lemin;

typedef struct				s_path_wrapper
{
	t_lst					*rooms;
	size_t					cost;
}							t_pth;

void				print_res(t_lemin *lem);
void				bfs(t_lemin *lem);
int					room_equals(t_room *room1, t_room *room2);
int 				room_free(pointer room);

#endif
