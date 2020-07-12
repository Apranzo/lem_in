#include "includes/lem_in.h"
# define START "##start"
# define END "##end"
# define JAIL "#"

static int			lgnl(int fd, char **line)
{
	int 			res;

	while ((res = ft_gnl(fd, line)) >= 0)
		if (ft_strncmp(*line, JAIL, 1) &&
				!ft_strcmp(*line, START) &&
				!ft_strcmp(*line, END))
			free(line);
	return (res);
}

int			is_num_valid(int value, char *str)
{
	char	*value_str;
	int		res;

	res = 0;
	value_str = ft_itoa(value);
	if (ft_strcmp(value_str, str + (str[0] == '+')) == 0)
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
	while ((res = lgnl(fd, &line)) > 0)
	{
		if (!alist_append(&lemin->raw, line))
			ft_error("Error\n", -1);
	}
	return (!res);
}

void 				parse_rooms(t_lemin lemin)
{
	t_alst			*x_cord;
	t_alst			*y_cord;
	t_xy			cord;
	size_t 			i;
	char 			**room;
	t_room			*new;

	i = 1;
	cord = (t_xy){-1, -1};
	x_cord = alist_new(2048, &int_equal, &int_compare);
	y_cord = alist_new(2048, &int_equal, &int_compare);
	while (!ft_cntwords(lemin.raw.data[i], '-'))
	{
		if (!(new = ft_memalloc(sizeof(t_room))) ||
				!(room = ft_strsplit(lemin.raw.data[i], ' ')) ||
				room[0] || room[1] || room[2])
			ft_error("Error\n", -1);
		cord.x = ft_atoi(room[1]);
		cord.y = ft_atoi(room[2]);
		if (!is_num_valid(cord.x, room[1]) || !is_num_valid(cord.y, room[2]) ||
				(x_cord->length < cord.x && x_cord->data[cord.x]) ||
				(y_cord->length < cord.y && x_cord->data[cord.y]))
			ft_error("Error\n", -1);
		alist_insert(x_cord, cord.x, (pointer) 1);
		alist_insert(y_cord, cord.y, (pointer) 1);
		ft_strcpy(new->name, room[0]);
		if (!ft_strcmp(lemin.raw.data[i - 1], START))
		{
			if (lemin.start)
				ft_error("Error\n", -1);
			lemin.start = new;

		}
		if (!ft_strcmp(lemin.raw.data[i - 1], END))
		{
			if (lemin.end)
				ft_error("Error\n", -1);
			lemin.end = new;
		}
	 	if (!hash_map_insert(&lemin.rooms, new->name, new))
	 		ft_error("Error\n", -1);
	 	ft_freematr(room);
	 	i++;
	}
//	if (!lemin.raw.data[i])
//		ft_error("Error\n", -1);
	alist_free(x_cord);
	alist_free(y_cord);
	alist_remove_range(&lemin.raw, 0, i);
}

void			parse_links(t_lemin lemin)
{
	size_t 			i;
	char 			**linked;
	t_room			*left;
	t_room			*right;

	i = 0;
	while (ft_cntwords(lemin.raw.data[i], '-'))
	{
		if(!(linked = ft_strsplit(lemin.raw.data[i], '-')) || !*linked || !*(linked + 1))
			ft_error("Error\n", -1);
		if (!(left = hash_map_lookup(&lemin.rooms, linked[0])) ||
			!(right = hash_map_lookup(&lemin.rooms, linked[1])) ||
			alist_contains(&left->links, NULL, right) ||
			alist_contains(&right->links, NULL, left))
			ft_error("Error\n", -1);
		alist_append(&left->links, right);
	}
}

int			parse_ants_amount(t_lemin lemin)
{
	int				num;

	num = ft_atoi(lemin.raw.data[0]);
	if (num <= 0 || !is_num_valid(num, lemin.raw.data[0]))
		ft_error("Error\n", -1);
	return (num);
}

static	void 		check_unuses(t_pair *pair)
{
	size_t			i;
	t_room			*room;

	room = pair->value;
	i = 0;
	while (room->links.length > i)
	{
		if (((t_room*)room->links.data[i])->level <= room->level)
		{
			((t_room*)room->links.data[i])->in--;
			alist_remove(&room->links, i);
		}
		else
			i++;
	}
	i = 0;
	while (room->links.length > i)
		((t_room*)room->links.data[i++])->in++;
}

static	void 		delete_dead_end(t_pair *pair)
{
	t_room *room;

	room = pair->value;
	if (!room->required && room->in == 0)
		alist_clear(&room->links);
	if (room->in < 0)
		ft_error("room->in < 0", -2);
}

static	void 		delete_forks(t_pair *pair)
{
	size_t			i;
	t_room			*room;

	room = pair->value;
	i = 0;
	while (room->links.length > 1 && room->links.length > i)
	{
		if (((t_room*)room->links.data[i])->in < 1)
		{
			((t_room*)room->links.data[i])->in--;
			alist_remove(&room->links, i);
		}
		else
			i++;
	}
}

int 				delete_unnecerarry(t_lemin *lemin)
{
	t_itr			*itr;

	if (!(itr = ft_memalloc(sizeof(t_itr))))
		ft_error("Error\n", -1);
	itr = hm_itr_load(lemin->rooms, itr);
	itr_foreach(itr, (void (*)(pointer)) &check_unuses);
	itr_foreach(itr, (void (*)(pointer)) &delete_dead_end);
	itr_free(itr);
}

int					main(void)
{
	t_lemin			lemin;

	ft_bzero(&lemin, sizeof(lemin));
	alist_init(&lemin.raw, 8192, &string_equal, &string_compare);
	hash_map_init(&lemin.rooms, &ft_hash, &room_equals);
	parse_ants_amount(lemin);
	parse_rooms(lemin);
	parse_links(lemin);
	if (!lemin.start || !lemin.end || !lemin.start->links.length)
		ft_error("Error\n", -1);
	bfs(&lemin);
	delete_unnecerarry(&lemin);

}