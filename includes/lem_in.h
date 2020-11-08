/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:56:15 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/10 19:27:53 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

# define START "##start"
# define END "##end"
# define JAIL "#"

typedef struct s_room	t_room;
typedef struct s_ant	t_ant;

struct					s_room
{
	char				*name;
	t_lst				*out;
	t_lst				*in;
	t_ant				*ant;
	int					asc_level;
	int					desc_level;
	int					required;
	t_xy				cords;
};

struct					s_ant
{
	t_room				*room;
	int					finished;
	int					started;
	size_t				number;
};

typedef struct			s_lemin
{
	t_lst				*raw;
	t_itr				*filtred;
	t_lst				*paths;
	t_lst				*ants;
	t_qu				*qu;
	size_t				amount;
	size_t				finished;
	t_hm				*rooms;
	t_room				*start;
	t_room				*end;
}						t_lemin;

typedef struct			s_path_wrapper
{
	t_lst				*rooms;
	size_t				cost;
}						t_pth;

typedef struct			s_fuck_the_system
{
	t_room				*room;
	t_hm				*black;
	t_qu				*qu;
	void				(*f_level)(t_room *child, t_room *parent);
	t_node				*(*get_first)(t_room *);
}						t_fck;

void					lmn_produce_output(t_lemin *lem,
											t_itr *itr,
											t_str_bld *bld);
void					print_input(const t_lemin *lem);
void					lmn_prepare_paths(const t_lemin *lem);
int						read_intput(int fd, t_lemin *lem);
void					create_ants(t_lemin *lem);
void					lmn_del_dead_end(const t_lst *lst);
void					lmn_check_unuses(const t_lst *lst);
void					lmn_alight(const t_lst *lst);
void					lmn_del_input_forks(const t_lst *lst);
void					lmn_del_output_forks(const t_lst *lst);
void					free_path(t_pth *pth);
int						build_path(const t_lemin *lem, t_lst *br);
void					find_path(t_lemin *lem);
t_room					*lmn_init_room(t_room *new, char **room);
void					parse_rooms(t_lemin *lem);
void					parse_links(t_lemin *lem);
int						parse_ants_amount(t_lemin *lem);
t_node					*get_out_first(t_room *room);
t_node					*get_in_first(t_room *room);
void					print_res(t_lemin *lem);
void					lmn_bfs_asc(t_lemin *lem);
void					lmt_bfs_desc(t_lemin *lem);
int						room_equals(t_room *room1, t_room *room2);
int						room_free(t_pntr room);

#endif
