#include <stdio.h>
#include <assert.h>
#include "includes/lem_in.h"
# define START "##start"
# define END "##end"
# define JAIL "#"

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

static int	validation(char **av, int **arr)
{
	size_t	i;

	i = 0;
	while (av[i])
	{
		(*arr)[i] = ft_atoi(av[i]);
		if (!is_num_valid((*arr)[i], av[i]))
			ft_error("Error\n", -1);
		i++;
	}
	return (i);
}

int 				read_intput(int fd, t_lemin *lemin)
{
	char 			*line;
	int 			res;

	line = NULL;
	while ((res = ft_gnl(fd, &line)) > 0)
	{
		if (!lemin->raw && !line)
			assert(0);
		if (!ft_lstappend(&lemin->raw, line))
			ft_error("read_input Error allocation\n", -1);
//		res = ft_atoi(lemin->raw->data[0]);
//		if (res)
//			ft_putnbr(res);
//		free(line);
	}
	return (!res);
}

void 				parse_rooms(t_lemin *lemin)
{
	t_alst			*x_cord;
	t_alst			*y_cord;
	t_xy			cord;
//	size_t 			i;
	t_node			*node;
	char 			**room;
	t_room			*new;

	node = lemin->raw;
	cord = (t_xy){-1, -1};
	x_cord = alist_new(2048, &int_equal, &int_compare);
	y_cord = alist_new(2048, &int_equal, &int_compare);
	while (!ft_strchr(node->data, '-'))
	{
		if (!strcmp(node->data, END) || !ft_strcmp(node->data, START))
			node = node->next;
		if (!(new = ft_memalloc(sizeof(t_room))) ||
				!(room = ft_strsplit(node->data, ' ')) ||
				!room[0] || !room[1] || !room[2])
			ft_error("Error\n", -1);
		new->asc_level = -1;
		new->desc_level = INT_MAX; // TODO CNECK
		cord.x = ft_atoi(room[1]);
		cord.y = ft_atoi(room[2]);
		if (!is_num_valid(cord.x, room[1]) || !is_num_valid(cord.y, room[2]) ||
				(x_cord->length < cord.x && x_cord->data[cord.x]) ||
				(y_cord->length < cord.y && x_cord->data[cord.y]))
			ft_error("Error\n", -1);
		alist_insert(x_cord, cord.x, (pointer) 1);
		alist_insert(y_cord, cord.y, (pointer) 1);
		new->name = strdup(room[0]); //TODO FIX IT
		if (!strcmp(node->prev->data, START))
		{
			if (lemin->start)
				ft_error("Error\n", -1);
			lemin->start = new;

		}
		if (!strcmp(node->prev->data, END))
		{
			if (lemin->end)
				ft_error("Error\n", -1);
			lemin->end = new;
		}
	 	if (!hm_insert(lemin->rooms, new->name, new))
	 		ft_error("Error\n", -1);
	 	ft_freematr(room);
	 	node = node->next;
	}
//	if (!lemin->raw->data[i])
//		ft_error("Error\n", -1);
	alist_free(x_cord);
	alist_free(y_cord);
	lemin->raw = node; //TODO free before
}

void				parse_links(t_lemin *lemin)
{
	t_node			*node;
	char 			**linked;
	t_room			*left;
	t_room			*right;

	node = lemin->raw;
	while (node && ft_cntwords(node->data, '-'))
	{
		if(!(linked = ft_strsplit(node->data, '-')) || !*linked || !*(linked + 1))
			ft_error("Error\n", -1);
		if (!(left = hm_lookup(lemin->rooms, linked[0])) ||
				!(right = hm_lookup(lemin->rooms, linked[1]))
//				||
//				alist_contains(&left->links, NULL, right) ||  // TODO check it
//				alist_contains(&right->links, NULL, left)
				)
			ft_error("Error\n", -1);
		ft_lstappend(&left->links, right);
		ft_lstappend(&right->links, left); //TODO check direction
		node = node->next;
	}
}

int			parse_ants_amount(t_lemin *lemin)
{
	assert(lemin->raw);
	lemin->ants = ft_atoi(lemin->raw->data);
	if (lemin->ants <= 0 || !is_num_valid(lemin->ants, lemin->raw->data))
		ft_error("Error\n", -1);
	lemin->raw = lemin->raw->next;
//	ft_putnbr(num);
	return (lemin->ants);
}

static	void 		check_unuses(t_pair *pair)
{
	t_room			*room;
	t_node			*node;

	room = pair->value;
	node = room->links;
	while (node)
	{
		if (((t_room*)node->data)->asc_level <= room->asc_level)
		{
			((t_room*)node->data)->in--;
			ft_lstdel(&node, NULL);
		}
		else
			node = node->next;
	}
	node = room->links;
	while (node)
	{
		((t_room *) node)->in++;
		node = node->next;
	}
}

static	void 		delete_dead_end(t_lemin *lemin, t_pair *pair)
{
	t_room *room;

	room = pair->value;
	if (!room->required && room->in == 0)
	{
		hm_remove(lemin->rooms, ((t_room*)room->links)->name);
		room->links = NULL;
	}
	if (room->in < 0)
		ft_error("room->in < 0", -2);
}

static	void 		del_input_forks(t_pair *pair) // TODO What?
{
	t_node			*node;
	t_room			*room;

	room = pair->value;
	node = room->links;
	while (node)
	{
		if (((t_room*)node->data)->in > 1)
		{
			((t_room*)node->data)->in--;
			ft_lstdel(&node, NULL);
		}
		else
			node = node->next;
	}
}

static	void 		del_output_forks(t_pair *pair)
{
	t_node			*node;
	t_room			*room;
	size_t			shortest;

	room = pair->value;
	shortest = room->desc_level;
	node = room->links;
	while (node)
	{
		shortest = shortest < ((t_room *) node->data)->desc_level ?
				   ((t_room *) node->data)->desc_level :
				   shortest;
		node = node->next;
	}
	node = room->links;
	if (node->next)
		while (node)
		{
			if (((t_room *) node->data)->desc_level != shortest)
				ft_lstdel(&node, NULL);
			else
				shortest = -1;
			node = node->next;
		}
	if (node)
		ft_error("del_output_forks\troom->links.length > 1", -2);
}

void 				delete_unnecerarry(t_lemin *lemin)
{
	t_itr			*itr;

	if (!(itr = ft_memalloc(sizeof(t_itr))))
		ft_error("Error\n", -1);
	itr = hm_itr_load(lemin->rooms, itr);
	itr_foreach(itr, (void (*)(pointer)) &check_unuses); //TODO удаление в итераторе
	itr_foreach(itr, (void (*)(pointer)) &delete_dead_end);
	itr_foreach(itr, (void (*)(pointer)) &del_input_forks);
	itr_foreach(itr, (void (*)(pointer)) &del_output_forks);
	itr_free(itr);
}

//void 				find_path(t_lemin *lemin)
//{
//	size_t 			i;
//	t_alst			*br;
//	t_room 			*room;
//	i = 0;
//	lemin->paths = alist_new(lemin->start->links.length, &pointer_equal, &pointer_compare);
//	while (i < lemin->paths->length)
//	{
//		br = alist_new(0, NULL, NULL);
//		alist_append(lemin->paths, br);
//		room = lemin->start->links.data[i];
//		while (room != lemin->end)
//		{
//			if (room->links.length > 1)
//				ft_error("find_path\troom->links > 1", -2);
//			alist_append(br, room);
//			room = *room->links.data;
//		}
//		i++;
//	}
//}

//static void			move(t_alst *lstroom)
//{
//	size_t			i;
//
//	i = lstroom->length - 1;
//	((t_room*)lstroom->data[i])->ant = 0;
//	i--;
//	while (i && i < lstroom->length)
//	{
//		((t_room*)lstroom->data[i])->ant = ((t_room*)lstroom->data[i + 1])->ant;
//		i--;
//	}
//}
//
//static int 			pass_ants(t_lemin *lem, size_t *number)
//{
//	size_t			i;
//	t_alst			*path;
//
//	i = 0;
//
//	if (*number == lem->ants && lem->end->ant == lem->ants) //TODO check it
//		return (0);
//	while (lem->paths->length > i)
//	{
//		path = lem->paths->data[i];
//		move(path);
//		if (*number < lem->ants)
//			((t_room*)path->data)->ant = *number++;
//	}
//	return (1);
//
//}
//
//static void			print(t_alst *lstroom)
//{
//	size_t			i;
//	t_room 			*room;
//
//	i = 0;
//	while (i < lstroom->length)
//	{
//		room = lstroom->data[i];
//		if (room->ant)
//			ft_printf("L%zu-%s", room->ant, room->name);
//		i++;
//	}
//}

//void				print_res(t_lemin *lem)
//{
//	size_t			number;
//	size_t			i;
//
//	number = 1;
//	i = 0;
//	while (lem->paths->length > i && number < lem->ants)
//			((t_room*)lem->paths->data[i++])->ant = number++;
//	while (pass_ants(lem, &number))
//	{
//		i = 0;
//		while (lem->paths->length > i)
//		{
//			if (i)
//				ft_putchar(' ');
//			print(lem->paths->data[i++]);
//		}
//		ft_putchar('\n');
//	}
//}

int					main(void)
{
	t_lemin			*lemin;
//	int y = 1000000;

	freopen("mmm", "r", stdin);

	if (!(lemin = ft_memalloc(sizeof(t_lemin)))
//	||
//			!(lemin->raw = alist_new(1000, &string_equal, &string_compare))
			)
		ft_error("main alloc error", -1);

	read_intput(STDIN_FILENO, lemin);
	assert(lemin->raw);
//	while (--y)
	parse_ants_amount(lemin);
//	ft_putnbr(parse_ants_amount(lemin));
	lemin->rooms = hm_new(&ft_hash, &string_equal);
	assert(lemin->rooms);
	parse_rooms(lemin);
	parse_links(lemin);
	if (!lemin->start || !lemin->end || !lemin->start->links)
		ft_error("Error\n", -1);
	bfs(lemin);
	delete_unnecerarry(lemin);
//	find_path(lemin);

}