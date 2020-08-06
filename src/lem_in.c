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

static void deb(t_lemin *lem)
{
	t_itr *itr;
	t_pair *pair;
	t_node	*node;
	t_room 	*room;

	if (!(itr = ft_memalloc(sizeof(t_itr))))
		ft_error("Error\n", -1);
	hm_itr_load(lem->rooms, itr);
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

static void pthdeb(t_lemin *lem)
{
	t_node	*path_node;
	t_pth 	*path;
	size_t i = 1;
	path_node = lem->paths->first;
	while (path_node)
	{
		path = ((t_pth *)path_node->data);
		ft_printf("\n++++++++++++++++++++++++++\nPath#%zu l: %zu\n", i++, path->rooms->length);
		pthpr(path->rooms);
		path_node = path_node->next;
	}
	ft_printf("\n");
}

static void pdeb(t_lemin *lem)
{
	t_node	*node;
	t_node	*path_node;
	t_pth 	*path;
	size_t i = 1;
	path_node = lem->paths->first;
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

int 				read_intput(int fd, t_lemin *lem)
{
	char 			*line;
	int 			res;

	line = NULL;
	while ((res = ft_gnl(fd, &line)) > 0 && line)
	{
		if (!lst_append(lem->raw, line))
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
	new->desc_level = -1;
	ft_freematr(room);
	return (new);
}

t_room				*lmn_check_status(t_lemin *lem, t_room *room, char **line)
{

	if (!strcmp(*line, END))
	{
		if (lem->end || !itr_has_more(lem->filtred))
			return (NULL);
		else
		{
			*line = itr_next(lem->filtred);
			(room->required = 1) && (lem->end = room);
			return (lmn_check_status(lem, room, line));
		}
	}
	else if (!ft_strcmp(*line, START))
	{
		if (lem->start || !itr_has_more(lem->filtred))
			return (NULL);
		else
		{
			*line = itr_next(lem->filtred);
			(room->required = 1) && (lem->start = room);
			return (lmn_check_status(lem, room, line));
		}
	}
	return (room);
}

void 				parse_rooms(t_lemin *lem)
{
	t_hash_map 		*cords;
	char 			*line;
	t_room			*new;

	cords = hm_new(&ft_str_hash, &string_equal);
//	pr_iter(lem->filtred);
	while (itr_has_more(lem->filtred) &&
			!ft_strchr(lem->filtred->_cur_node->data, '-'))
	{
		line = itr_next(lem->filtred);
		if (line[0] == 'L'
			|| !(new = ft_memalloc(sizeof(t_room)))
			|| !lmn_check_status(lem, new, &line)
			|| hm_lookup(cords, ft_strchr(line, ' '))
			|| !(new = lmn_init_room(new ,ft_strsplit(line, ' '))))
			ft_error("Error\n", -1);
		hm_insert(cords, ft_strchr(line, ' '), ft_strchr(line, ' '));
//		if ((x_cord->length - 1 < new->cords.x || x_cord->data[new->cords.x]) ||
//				(y_cord->length  - 1 < new->cords.y || x_cord->data[new->cords.y]))
//			ft_error("Error\n", -1);
	 	if (!hm_insert(lem->rooms, new->name, new))
	 		ft_error("Error\n", -1);
	}
	if (!itr_has_more(lem->filtred))
		ft_error("Error\n", -1);
	hm_free(cords, NULL, NULL);
}

void				parse_links(t_lemin *lem)
{
	char			*line;
	char 			**linked;
	t_room			*left;
	t_room			*right;

	while ((line = itr_next(lem->filtred)) && ft_cntwords(line, '-'))
	{
		if(!(linked = ft_strsplit(line, '-')) || !*linked || !*(linked + 1))
			ft_error("Error\n", -1);
		if (!(left = hm_lookup(lem->rooms, linked[0])) ||
			!(right = hm_lookup(lem->rooms, linked[1])) ||
			lst_contains(left->out, (f_equal) &room_equals, right) ||
				lst_contains(right->out, (f_equal) &room_equals, left))
			ft_error("Error\n", -1);
		ft_freematr(linked);
		lst_append(right->out, left);
		lst_append(left->out, right);
		lst_append(right->in, left);
		lst_append(left->in, right);
	}
}

int			parse_ants_amount(t_lemin *lem)
{
	char			*str;

	str = itr_next(lem->filtred);
	lem->amount = str && str[0] != '-' ? ft_atoi(str) : -1;
	if (lem->amount <= 0 || !is_num_valid(lem->amount, str))
		ft_error("Error\n", -1);
//	ft_putnbr(num);
	return (lem->amount);
}

static	void 		check_unuses(t_room	*room)
{
	t_node			*node;
	pointer			*data;

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
	t_node *tmp;

	if (!room->required && room->in->length && !room->out->length)
	{
		node = room->in->first;
		while (node)
		{
			tmp = node->next;
			lst_rm_data(((t_room*)node->data)->out, (f_equal) &room_equals, room);
			lst_rm_data(room->in, (f_equal) &room_equals, node->data);
			node = tmp;
		}
	}
	else if (!room->required && !room->in->length && room->out->length)
	{
		node = room->out->first;
		while (node)
		{
			tmp = node->next;
			lst_rm_data(((t_room*)node->data)->in, (f_equal) &room_equals, room);
			lst_rm_data(room->out, (f_equal) &room_equals, node->data);
			node = tmp;
		}
	}
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
	itr = lst_itr_load(lst, NULL, NULL);
	itr_foreach(itr, (void (*)(pointer)) &delete_dead_end);
	lst_free(lst, NULL);
	itr_free(itr);

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
			if (shortest < 0 || ((t_room *) node->data)->desc_level != shortest)
				lst_rm_entry(room->out, node);
			else
				shortest = -1;
			node = node->next;
		}
	}
	if (!room->required && room->out->length > 1)
		ft_error("del_output_forks\troom->links.length > 1", -2);
}

void 				delete_unnecerarry(t_lemin *lem)
{
	t_itr			*itr;
	t_lst 			*lst;

	lst = hm_lst(lem->rooms, NULL);
	lst_sort(lst, (f_compare) &comp_bfs_asc);
	itr = lst_itr_load(lst, NULL, NULL);
	itr_foreach(itr, (void (*)(pointer)) &check_unuses); //TODO удаление в итераторе
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
	bfs_desc_level(lem);
	itr_foreach(itr, (void (*)(pointer)) &del_output_forks);
	itr_free(itr);
	lst_free(lst, NULL);
}


static void free_path(t_pth *pth)
{
	lst_free(pth->rooms, NULL);
	free(pth);
}

int build_path(const t_lemin *lem, t_lst *br)
{
	t_node 			*entry;
	t_room 			*room;

	entry = br->first;
	while (entry->data != lem->end)
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

void 				find_path(t_lemin *lem)
{
	size_t 			i;
	t_lst			*br;
	t_lst			*links;
	t_node			*node;
	t_pth 			*path;

	i = 0;
	lem->paths = lst_new();
	links = lem->start->out;
	while (i < links->length)
	{
		br = lst_new();
		path = ft_memalloc(sizeof(t_pth));
		path->rooms = br;
		lst_append(lem->paths, path);
		lst_append(br, lst_nth_data(links, i));
		i++;
	}
	node = lem->paths->first;
	while (node)
	{
		br = ((t_pth *)node->data)->rooms;
		if(!build_path(lem, br))
			lst_rm_entry(lem->paths, node);
		node = node->next;
	}
	if (!lem->paths->length)
		ft_error("Error\n", -1);
//	pthdeb(lem);
}


int 				input_filter_predict(char *line)
{
	return (ft_strncmp(line, JAIL, 1) ||
			(!ft_strcmp(line, START) ||	!ft_strcmp(line, END)));
}

static void			cr_ants(t_lemin *lem)
{
	t_lst			*ants;
	t_ant 			*ant;
	size_t 			num;

	num = lem->amount;
	ants = lst_new();
	while (num)
	{
		if (!(ant = malloc(sizeof(t_ant))))
			ft_error("Error\n", -1);
		ant->room = NULL;
		ant->finished = 0;
		ant->started = 0;
		ant->number = num;
		lst_append(ants, ant);
		num--;
	}
	lem->ants = ants;
	if (!(lem->qu = qu_by_lst(lem->ants)))
		ft_error("Error\n", -1);
}


int					main(void)
{

	freopen("mmm", "r", stdin);

	if (!(lemin = ft_memalloc(sizeof(t_lemin))) ||
			!(lemin->raw = lst_new()))
		ft_error("main alloc error", -1);
	read_intput(STDIN_FILENO, lemin);
	if (!(lemin->filtred = lst_itr_load(lemin->raw, NULL,
										(f_prdct) input_filter_predict)))
		ft_error("main alloc error", -1);
	parse_ants_amount(lemin);
	lemin->rooms = hm_new(&ft_str_hash, &string_equal);
	parse_rooms(lemin);
	parse_links(lemin);
	if (!lemin->start || !lemin->end || !lemin->start->out)
		ft_error("Error\n", -1);
	cr_ants(lemin);
	bfs_asc_level(lemin);
	delete_unnecerarry(lemin);
	find_path(lemin);
	print_res(lemin);
//	free(lemin->raw);
	lst_free(lemin->raw, free);
	itr_free(lemin->filtred);
	lst_free(lemin->paths, (f_free) &free_path);
	lst_free(lemin->ants, free);
	qu_free(lemin->qu);
	hm_free(lemin->rooms, NULL, (f_free) &room_free);
	free(lemin);
}