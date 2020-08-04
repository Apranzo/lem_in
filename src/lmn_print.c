#include "../includes/lem_in.h"

int 			cmpr_lst_ln(t_pth *lft, t_pth *rght)
{
	return (lft->rooms->length - rght->rooms->length);
}

void 		sum_prev_ln(t_node *node)
{
	t_pth 			*pth;

	pth = node->data;
	pth->cost = 0;
	while (node->prev)
	{
		pth->cost += pth->rooms->length - ((t_pth *)node->prev->data)->rooms->length;
		node = node->prev;
	}
}

static int 				resolv_path(t_pth *pth, int ants, int number)
{
	return (ants - number + 1 > pth->cost);
}

static void			move(t_lst *lst)
{
	t_node			*node;

	node = lst->last;
	((t_room*)node->data)->ant = node->prev ? ((t_room*)node->prev->data)->ant : ((t_room*)node->data)->ant;
	node = node->prev;
	while (node && node->prev)
	{
		((t_room*)node->data)->ant = ((t_room*)node->prev->data)->ant;
		node = node->prev;
	}
	if(node)
		((t_room*)node->data)->ant = 0;
}

int					print(t_lst *lst)
{
	t_node 			*node;
	int				printed;

	printed = 0;
	node = lst->first;
	while (node)
	{
		if (((t_room*)node->data)->ant)
		{
			printed += ft_printf("L%zu-%s", ((t_room *) node->data)->ant,  ((t_room *) node->data)->name);
			if (node->next && ((t_room *) node->next->data)->ant)
				ft_printf(" ");
		}
		node = node->next;
	}
	return(printed);
}

static int					pass_ants(t_pth *pth, size_t *number, size_t ants)
{

	move(pth->rooms);
	if (resolv_path(pth, ants, *number))
		((t_room *) pth->rooms->first->data)->ant = (*number)++;
	return (print(pth->rooms));
}

void				pr_by_ants(t_lemin *lemin)
{
	t_itr			*itr;
	t_ant 			*ant;

	lst_sort(lemin->paths, (f_compare) &cmpr_lst_ln);
	lst_foreach(lemin->paths, (f_map) &sum_prev_ln);
	itr = lst_itr_load(lemin->ants, NULL, NULL);
	while (itr_has_more(itr))
	{
		ant = itr_next(itr);

	}

}

void				print_res(t_lemin *lem)
{
	size_t			number;
	t_node			*node;
	t_node			*nroom;
	t_pth			*pth;
	t_itr			*itr;
	char			*line = ft_strnew(0);
	int 			printed;

	itr = lst_itr_load(lem->raw, NULL, NULL);
	while (itr_has_more(itr))
		ft_printf("%s\n", itr_next(itr));
	ft_printf("\n");
	number = 1;
	lst_sort(lem->paths, (f_compare) &cmpr_lst_ln);
	lst_foreach(lem->paths, (f_map) &sum_prev_ln);
	while (lem->finished < lem->amount)
	{
		node = lem->paths->first;
		printed = 0;
		while (node != lem->paths->last)
		{
			pth = node->data;
			move(pth->rooms);
			if (resolv_path(pth, lem->amount, number))
				((t_room *) pth->rooms->first->data)->ant = number++;
			nroom = pth->rooms->first;
			while (nroom)
			{
				if (((t_room*)nroom->data)->ant)
				{
					printed += ft_sprintf(&line, "L%zu-%s ", ((t_room *) nroom->data)->ant,  ((t_room *) nroom->data)->name);
//					if (nroom->next && ((t_room *) nroom->next->data)->ant)
//						ft_printf(" ");
				}
				nroom = nroom->next;
			}
			if (((t_room *) pth->rooms->last->data)->ant)
				lem->finished++;
			node = node->next;
		}
		line[printed - 1] = '\n';
	}
	if(line[printed - 1] == ' ')
		line[printed - 1] = '\n';
	ft_putstr(line);
//	ft_printf("\n");
}