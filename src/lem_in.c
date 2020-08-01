#include <stdio.h>
#include <assert.h>
#include "includes/lem_in.h"
# define START "##start"
# define END "##end"
# define JAIL "#"

static t_lemin			*lemin;

void pr_room(const t_room *room) {
	printf("NAME %s\tasc %d\tdesc %d\tin %zu\treq %d\n",
		   room->name, room->asc_level, room->desc_level, room->in->length, room->required);
}

void				pr_iter(t_itr *itr)
{
	t_node *node;

	node = itr->_cur_node;

	ft_printf("\n********************\n");
	while (node)
	{
		pr_room(node->data);
		node = node->next;
	}
	ft_printf(":::::::::::::::::::::::::::::::\n");
}

static void deb(t_lemin *lemin)
{
	t_itr *itr;
	t_pair *pair;
	t_node	*node;
	t_room 	*room;

	if (!(itr = ft_memalloc(sizeof(t_itr))))
		ft_error("Error\n", -1);
	hm_itr_load(lemin->rooms, itr);
	while (itr_has_more(itr))
	{
		pair = itr_next(itr);
		room = pair->value;
		pr_room(pair->value);
		node = room->out->first;
		printf("out:\t");
		while (node)
		{
			printf("%s,\t", ((t_room*)node->data)->name);
			node = node->next;
		}
		printf("\n");
		node = room->in->first;
		printf("in:\t\t");
		while (node)
		{
			printf("%s,\t", ((t_room*)node->data)->name);
			node = node->next;
		}
		printf("\n------------------------------\n");
	}
}

static void pthpr(t_lst *lst)
{
	t_node	*node;
	node = lst->first;
	while (node)
	{
		ft_printf("%s(L%d)->", ((t_room*)node->data)->name, ((t_room*)node->data)->ant);
		node = node->next;
	}
	ft_printf("\n");
}

static void pthdeb(t_lemin *lemin)
{
	t_node	*node;
	t_node	*path_node;
	t_pth 	*path;
	size_t i = 1;
	path_node = lemin->paths->first;
	while (path_node)
	{
		path = ((t_pth *)path_node->data);
		ft_printf("\n++++++++++++++++++++++++++\nPath#%zu l: %zu\n", i++, path->rooms->length);
		pthpr(path->rooms);
		path_node = path_node->next;
	}
	ft_printf("\n");
}

static void pdeb(t_lemin *lemin)
{
	t_node	*node;
	t_node	*path_node;
	t_pth 	*path;
	size_t i = 1;
	path_node = lemin->paths->first;
	ft_printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
	while (path_node)
	{
		path = ((t_pth *)path_node->data);
		ft_printf("\n++++++++++++++++++++++++++\nPath#%zu\n", i++);
		node = path->rooms->first;
		while (node)
		{
			ft_printf("%s->", ((t_room*)node->data)->name);
			node = node->next;
		}
		path_node = path_node->next;
	}
	ft_printf("\n");
}


int			is_num_valid(int value, char *str)
{
	char	*value_str;
	int		res;

	res = 0;
	value_str = ft_itoa(value);
	if (strcmp(value_str, str + (str[0] == '+')) == 0)
		res = 1;
	if (value_str)
		free(value_str);
	return (res);
}

int 				read_intput(int fd, t_lemin *lemin)
{
	char 			*line;
	int 			res;

	line = NULL;
	while ((res = ft_gnl(fd, &line)) > 0 && line)
	{
		if (!lst_append(lemin->raw, line))
			ft_error("read_input Error allocation\n", -1);
	}
	return (!res);
}

t_room *lmn_init_room(t_room *new, char **room)
{
	if (!new || !room ||
			!room[0] || !room[1] || !room[2] ||
			!(new->out = lst_new()) ||
			!(new->in = lst_new()))
		return (NULL);
	new->name = strdup(room[0]);
	new->cords.x = ft_atoi(room[1]);
	new->cords.y = ft_atoi(room[2]);
	if (!is_num_valid(new->cords.x, room[1]) || !is_num_valid(new->cords.y, room[2]))
		return (NULL);
	new->asc_level = -1;
//	new->in = 0;
//	new->ant = 0;
	new->desc_level = -1;
	ft_freematr(room);
	return (new);
}

t_room				*lmn_check_status(t_lemin *lemin, t_room *room, char **line)
{

	if (!strcmp(*line, END))
	{
		if (lemin->end || !itr_has_more(lemin->filtred))
			return (NULL);
		else
		{
			*line = itr_next(lemin->filtred);
			(room->required = 1) && (lemin->end = room);
			return (lmn_check_status(lemin, room, line));
		}
	}
	else if (!ft_strcmp(*line, START))
	{
		if (lemin->start || !itr_has_more(lemin->filtred))
			return (NULL);
		else
		{
			*line = itr_next(lemin->filtred);
			(room->required = 1) && (lemin->start = room);
			return (lmn_check_status(lemin, room, line));
		}
	}
	return (room);
}

void 				parse_rooms(t_lemin *lemin)
{
	t_hash_map 		*cords;
	char 			*line;
	t_room			*new;

	cords = hm_new(&ft_str_hash, &string_equal);
//	pr_iter(lemin->filtred);
	while (itr_has_more(lemin->filtred) &&
			!ft_strchr(lemin->filtred->_cur_node->data, '-'))
	{
		line = itr_next(lemin->filtred);
		if (line[0] == 'L'
			|| !(new = ft_memalloc(sizeof(t_room)))
			|| !lmn_check_status(lemin, new, &line)
			|| hm_lookup(cords, ft_strchr(line, ' '))
			|| !(new = lmn_init_room(new ,ft_strsplit(line, ' '))))
			ft_error("Error\n", -1);
		hm_insert(cords, ft_strchr(line, ' '), ft_strchr(line, ' '));
//		if ((x_cord->length - 1 < new->cords.x || x_cord->data[new->cords.x]) ||
//				(y_cord->length  - 1 < new->cords.y || x_cord->data[new->cords.y]))
//			ft_error("Error\n", -1);
	 	if (!hm_insert(lemin->rooms, new->name, new))
	 		ft_error("Error\n", -1);
	}
	if (!itr_has_more(lemin->filtred))
		ft_error("Error\n", -1);
	hm_free(cords);
}

void				parse_links(t_lemin *lemin)
{
	char			*line;
	char 			**linked;
	t_room			*left;
	t_room			*right;

	while ((line = itr_next(lemin->filtred)) && ft_cntwords(line, '-'))
	{
		if(!(linked = ft_strsplit(line, '-')) || !*linked || !*(linked + 1))
			ft_error("Error\n", -1);
		if (!(left = hm_lookup(lemin->rooms, linked[0])) ||
			!(right = hm_lookup(lemin->rooms, linked[1])) ||
			lst_contains(left->out, (f_equal) &room_equals, right) ||
				lst_contains(right->out, (f_equal) &room_equals, left))
			ft_error("Error\n", -1);
		lst_append(right->out, left);
		lst_append(left->out, right);
		lst_append(right->in, left);
		lst_append(left->in, right);
	}
}

int			parse_ants_amount(t_lemin *lemin)
{
	char			*str;

	str = itr_next(lemin->filtred);
	lemin->ants = str && str[0] != '-' ? ft_atoi(str) : -1;
	if (lemin->ants <= 0 || !is_num_valid(lemin->ants, str))
		ft_error("Error\n", -1);
	lemin->raw->first = lemin->raw->first->next;
//	ft_putnbr(num);
	return (lemin->ants);
}

static	void 		check_unuses(t_room	*room)
{
	t_node			*node;
//	t_node			*tmp; TODO free maybe

//	room = pair->value;
	node = room->out->first;
	while (node)
	{
		if (room->asc_level < 0)
		{
			lst_rm_data(((t_room *) node->data)->out, (f_equal) &room_equals, room);
			lst_rm_data(((t_room *) node->data)->in, (f_equal) &room_equals, room);
			lst_rm_data(room->in, (f_equal) &room_equals, node->data);
			lst_rm_data(room->out, (f_equal) &room_equals, node->data);
		}
		else if (((t_room*)node->data)->asc_level == room->asc_level)
		{
			lst_rm_data(room->in, (f_equal) &room_equals, node->data);
			lst_rm_data(((t_room *) node->data)->out, (f_equal) &room_equals, room);
			lst_rm_data(room->out, (f_equal) &room_equals, node->data);
			lst_rm_data(((t_room *) node->data)->in, (f_equal) &room_equals, room);
		}
		node = node->next;
	}
}

static	void 		alight(t_room	*room)
{
	t_node			*node;
//	t_node			*tmp; TODO free maybe
	node = room->out->first;
	while (node)
	{
		if (((t_room*)node->data)->asc_level < room->asc_level)
		{
			lst_rm_data(room->out, (f_equal) &room_equals, node->data);
			lst_rm_data(((t_room *) node->data)->in, (f_equal) &room_equals, room);
		}
		node = node->next;
	}
}

static	void 		delete_dead_end(t_room	*room)
{
	t_node *node;

	if (!room->required && room->in->length && !room->out->length)
	{
		node = room->in->first;
		while (node)
		{
			lst_rm_data(((t_room*)node->data)->out, (f_equal) &room_equals, room);
			lst_rm_data(room->in, (f_equal) &room_equals, node->data);
			node = node->next;
		}
	}
	else if (!room->required && !room->in->length && room->out->length)
	{
		node = room->out->first;
		while (node)
		{
			lst_rm_data(((t_room*)node->data)->in, (f_equal) &room_equals, room);
			lst_rm_data(room->out, (f_equal) &room_equals, node->data);
			node = node->next;
		}
	}
//	if (room->in < 0)
//		ft_error("room->in < 0", -2);
}

static int			comp_bfs_asc(t_room* left, t_room *right)
{
	if (left->asc_level > right->asc_level)
		return (1);
	else if (left->asc_level < right->asc_level)
		return (-1);
	return (0);
}

static int			comp_bfs_desc(t_room* left, t_room *right)
{
	if (left->asc_level > right->asc_level)
		return (-1);
	else if (left->asc_level < right->asc_level)
		return (1);
	return (0);
}

static void			dde()
{
	t_itr			*itr;
	t_lst 			*lst;

	lst = hm_lst(lemin->rooms, NULL);
	lst_sort(lst, (f_compare) &comp_bfs_asc);
	lst_sort(lst, (f_compare) &comp_bfs_asc);
	itr = lst_itr_load(lst, NULL, NULL);
	itr_foreach(itr, (void (*)(pointer)) &delete_dead_end);

}

static	void 		del_input_forks(t_room	*room) // TODO What?
{
	t_node			*node;

	node = room->in->first;
	while (!room->required && node)
	{
		if (!((t_room*)node->data)->required && room->in->length != 1)
		{
			lst_rm_entry(room->in, node);
			lst_rm_data(((t_room*)node->data)->out, (f_equal) &room_equals, room);
			dde();
		}
		node = node->next;
	}
}

static	void 		del_output_forks(t_room	*room)
{
	t_node			*node;
	int				shortest;

	shortest = INT_MAX;
	node = room->out->first;
	if (room->required)
		return ;
	while (node)
	{
		shortest = ((t_room *) node->data)->desc_level > 0 &&
					shortest > ((t_room *) node->data)->desc_level ?
				   ((t_room *) node->data)->desc_level :
				   shortest;
		node = node->next;
	}
	if (room->out->length > 1)
	{
		node = room->out->first;
		while (node) {
			if (((t_room *) node->data)->desc_level != shortest)
				lst_rm_entry(room->out, node);
			else
				shortest = -1;
			node = node->next;
		}
	}
	if (!room->required && room->out->length > 1)
		ft_error("del_output_forks\troom->links.length > 1", -2);
}

static int			filtr_bfs(t_room* room)
{
	return (room->asc_level > 0);
}

void 				delete_unnecerarry(t_lemin *lemin)
{
	t_itr			*itr;
	t_lst 			*lst;

	lst = hm_lst(lemin->rooms, NULL);
	lst_sort(lst, (f_compare) &comp_bfs_asc);
	itr = lst_itr_load(lst, NULL, NULL);
//	pr_iter(itr);
//	if (!(itr = bfs_trip(lemin->start, lemin->end, NULL, &get_out_first)))
//		ft_error("Error\n", -1);
//	hm_itr_load(lemin->rooms, itr);
	//deb(lemin);
	itr_foreach(itr, (void (*)(pointer)) &check_unuses); //TODO удаление в итераторе
	//deb(lemin);
	itr_reset(itr);
	itr_foreach(itr, (void (*)(pointer)) &alight);
	lst_sort(lst, (f_compare) &comp_bfs_asc);
	lst_itr_load(lst, itr, NULL);
	itr_foreach(itr, (void (*)(pointer)) &delete_dead_end);
	lst_sort(lst, (f_compare) &comp_bfs_asc);
	lst_itr_load(lst, itr, NULL);
	//deb(lemin);
	itr_foreach(itr, (void (*)(pointer)) &del_input_forks);
	lst_sort(lst, (f_compare) &comp_bfs_desc);
	lst_itr_load(lst, itr, NULL);
	bfs_desc_level(lemin);
	//deb(lemin);
	itr_foreach(itr, (void (*)(pointer)) &del_output_forks);
	//deb(lemin);
	itr_free(itr);
}

int build_path(const t_lemin *lemin, t_lst *br)
{
	t_node 			*entry;
	t_room 			*room;

	entry = br->first;
	while (entry->data != lemin->end)
	{
		room = entry->data;
		if (room->out->length > 1)
			ft_error("find_path\troom->links > 1", -2);
		if (!room->out->length)
			return (0);  //43 45 60
		lst_append(br, room->out->first->data);
		entry = entry->next;
	}
	return (1);
}

void 				find_path(t_lemin *lemin)
{
	size_t 			i;
	t_lst			*br;
	t_lst			*links;
	t_node			*node;
	t_pth 			*path;

	i = 0;
	lemin->paths = lst_new();
	links = lemin->start->out;
	while (i < links->length)
	{
		br = lst_new();
		path = ft_memalloc(sizeof(t_pth));
		path->rooms = br;
		lst_append(lemin->paths, path);
		lst_append(br, lst_nth_data(links, i));
		i++;
	}
	node = lemin->paths->first;
	while (node)
	{
		br = ((t_pth *)node->data)->rooms;
		if(!build_path(lemin, br))
			lst_rm_entry(lemin->paths, node);
		node = node->next;
	}
	if (!lemin->paths->length)
		ft_error("Error\n", -1);
//	pthdeb(lemin);
}


int 				input_filter_predict(char *line)
{
	return (ft_strncmp(line, JAIL, 1) ||
			(!ft_strcmp(line, START) ||	!ft_strcmp(line, END)));
}


int					main(void)
{

	freopen("mmm", "r", stdin);

	if (!(lemin = ft_memalloc(sizeof(t_lemin))) ||
			!(lemin->raw = lst_new()))
		ft_error("main alloc error", -1);
	read_intput(STDIN_FILENO, lemin);
	if (!(lemin->filtred = lst_itr_load(lemin->raw, lemin->filtred,
										(f_prdct) input_filter_predict)))
		ft_error("main alloc error", -1);
//	while (--y)
	parse_ants_amount(lemin);
//	pr_iter(lemin->filtred);
//	ft_putnbr(parse_ants_amount(lemin));
	lemin->rooms = hm_new(&ft_str_hash, &string_equal);
	assert(lemin->rooms);
//	pr_iter(lemin->filtred);
	parse_rooms(lemin);
//	pr_iter(lemin->filtred);
	parse_links(lemin);
	//deb(lemin);
	if (!lemin->start || !lemin->end || !lemin->start->out)
		ft_error("Error\n", -1);
//	itr = bfs_trip(lemin->start, lemin->end, NULL);
//	pr_iter(itr);
//	lemin->start->asc_level = 0;
//	lemin->end->desc_level = 0;
	bfs_asc_level(lemin);
//	lemin->start->desc_level = INT_MAX;
//	lemin->end->asc_level = INT_MAX;
//	lemin->start->desc_level = INT_MAX;
//	lemin->start->asc_level = 0;
	////deb(lemin);
	delete_unnecerarry(lemin);
	//deb(lemin);
	find_path(lemin);
//	pdeb(lemin);
	print_res(lemin);
}