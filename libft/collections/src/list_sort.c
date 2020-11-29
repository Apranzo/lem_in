/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:06:45 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

static void		sort_internal(t_node *pivot,
		t_node **less_lst, t_node **more_lst,
		t_fcompare compare_func)
{
	t_node		*rover;
	t_node		*next;

	rover = pivot->next;
	while (rover)
	{
		next = rover->next;
		if (compare_func(rover->data, pivot->data) < 0)
		{
			rover->prev = NULL;
			rover->next = *less_lst;
			if (*less_lst)
				(*less_lst)->prev = rover;
			*less_lst = rover;
		}
		else
		{
			rover->prev = NULL;
			rover->next = *more_lst;
			if (*more_lst)
				(*more_lst)->prev = rover;
			*more_lst = rover;
		}
		rover = next;
	}
}

static void		insert_pivot(t_node **node,
							t_node *pivot,
							const t_node *less_lst,
							t_node *less_lst_end)
{
	if (!less_lst)
	{
		pivot->prev = NULL;
		*node = pivot;
	}
	else
	{
		pivot->prev = less_lst_end;
		less_lst_end->next = pivot;
	}
}

static t_node	*lst_sort_internal(t_node **node,
									t_fcompare compare_func)
{
	t_node *pivot;
	t_node *less_lst;
	t_node *more_lst;
	t_node *less_lst_end;
	t_node *more_lst_end;

	if (!node || !compare_func)
		return (NULL);
	if (!*node || !(*node)->next)
		return (*node);
	pivot = *node;
	less_lst = NULL;
	more_lst = NULL;
	sort_internal(pivot, &less_lst, &more_lst, compare_func);
	less_lst_end = lst_sort_internal(&less_lst, compare_func);
	more_lst_end = lst_sort_internal(&more_lst, compare_func);
	*node = less_lst;
	insert_pivot(node, pivot, less_lst, less_lst_end);
	pivot->next = more_lst;
	if (more_lst)
		more_lst->prev = pivot;
	return (!more_lst ? pivot : more_lst_end);
}

void			lst_sort(t_lst *lst, t_fcompare compare_func)
{
	lst->last = lst_sort_internal(&lst->first, compare_func);
}
