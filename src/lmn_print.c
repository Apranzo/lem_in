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

void			print(t_lst *lst)
{
	t_node 			*node;

	node = lst->first;
	while (node)
	{
		if (((t_room*)node->data)->ant)
		{
			ft_printf("L%zu-%s", ((t_room *) node->data)->ant,  ((t_room *) node->data)->name);
			if (node->next && ((t_room *) node->next->data)->ant)
				ft_printf(" ");
		}
		node = node->next;
	}
}

static void 		pass_ants(t_pth *pth, size_t *number, size_t ants)
{

	move(pth->rooms);
	if (resolv_path(pth, ants, *number))
		((t_room *) pth->rooms->first->data)->ant = (*number)++;
	print(pth->rooms);
}

void				print_res(t_lemin *lem)
{
	size_t			number;
	t_node			*node;
	t_pth			*pth;
	t_itr			*itr;

	itr = lst_itr_load(lem->raw, NULL, NULL);
	while (itr_has_more(itr))
		ft_printf("%s\n", itr_next(itr));
	ft_printf("\n");
	number = 1;
	lst_sort(lem->paths, (f_compare) &cmpr_lst_ln);
	lst_foreach(lem->paths, (f_map) &sum_prev_ln);
	node = lem->paths->first;
	while (lem->finished < lem->ants)
	{
		pth = node->data;
		pass_ants(pth, &number, lem->ants);
		if (((t_room*)pth->rooms->last->data)->ant)
			lem->finished++;
		if (node == lem->paths->last)
		{
			node = lem->paths->first;
			ft_printf("\n");
		}
		else
		{
			ft_printf(" ");
			node = node->next;
		}
	}
	ft_printf("\n");
}