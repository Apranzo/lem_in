#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/includes/libft.h"

typedef struct s_room t_room;
typedef struct s_ant t_ant;

struct				s_room
{
	char			*name;
	t_lst 			*out;
	t_lst 			*in;
	t_ant			*ant;
	int				asc_level;
	int				desc_level;
	int				required;
	t_xy			cords;
};

struct 		s_ant
{
	t_room			*room;
	int				finished;
	int				started;
	int 			number;
};


typedef struct		s_lemin
{
	t_lst 			*raw;
	t_itr 			*filtred;
	t_lst 			*paths;
	t_lst 			*ants;
	t_qu 			*qu;
	int	 			amount;
	int	  			finished;
	t_hash_map 		*rooms;
	t_room			*start;
	t_room			*end;
}					t_lemin;

typedef struct				s_path_wrapper
{
	t_lst					*rooms;
	size_t					cost;
}							t_pth;


t_node 				*get_out_first(t_room *room);
t_node 				*get_in_first(t_room *room);
t_itr 				*bfs_trip(t_room *start, t_room *end, t_itr *itr,
							   t_node *(*get_first)(t_room *));
void				print_res(t_lemin *lem);
void				bfs_asc_level(t_lemin *lem);
void				bfs_desc_level(t_lemin *lem);
int					room_equals(t_room *room1, t_room *room2);
int 				room_free(pointer room);

#endif
