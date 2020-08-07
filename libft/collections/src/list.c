/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:56:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 17:58:39 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void					lst_clear(t_lst *lst, f_free free_data)
{
	t_node				*entry;
	t_node				*next;

	entry = lst->first;
	while (entry)
	{
		next = entry->next;
		if (free_data)
			free_data(entry->data);
		free(entry);
		entry = next;
	}
	lst->first = NULL;
	lst->last = NULL;
	lst->length = 0;
}

void				lst_free(t_lst *lst, f_free free_data)
{
	lst_clear(lst, free_data);
	free(lst);
}

t_node				*lst_prepend(t_lst *lst, pointer data)
{
	t_node			*new;

	if (!lst || !(new = ft_node_prepend(&lst->first, data)))
		return (NULL);
	lst->length++;
	return (new);
}

t_node				*lst_append(t_lst *lst, pointer data)
{
	t_node			*new;

	if (!lst || !(new = ft_node_append(&lst->last, data)))
		return (NULL);
	if (!lst->length)
		lst->first = new;
	lst->length++;
	return (new);
}

t_lst				*lst_new()
{
	return (ft_memalloc(sizeof(t_lst)));
}

t_node				*lst_nth_entry(t_lst *lst, size_t index)
{
	t_node			*entry;
	size_t			i;

	i = 0;
	entry = NULL;
	if (lst->length / 2 > index)
	{
		entry = lst->first;
		while (i++ < index)
			entry = entry->next;
	}
	else if(lst->length > index)
	{
		entry = lst->last;
		while (i++ < lst->length - index - 1)
			entry = entry->prev;
	}
	return (entry);
}

pointer			lst_nth_data(t_lst *lst, size_t index)
{
	t_node		*entry;

	entry = lst_nth_entry(lst, index);
	return (entry ? entry->data : NULL);
}

pointer				*lst_to_array(t_lst *lst)
{
	t_node			*rover;
	pointer			*array;
	size_t			i;

	if (!(array = ft_tmalloc(sizeof(pointer),  lst->length + 1)))
		return (NULL);
	array[lst->length] = NULL;
	i = 0;
	rover = lst->first;
	while (i < lst->length)
	{
		array[i] = rover->data;
		rover = rover->next;
		i++;
	}
	return (array);
}

t_node				*lst_rm_entry(t_lst *lst, t_node *entry)
{
	t_node			*next;

	if((entry = ft_node_del(entry, NULL)))
	{
		if (entry == lst->first)
			lst->first = lst->first->next;
		if (entry == lst->last)
			lst->last = lst->last->prev;
		lst->length--;
		next = entry->next;
		entry->prev = NULL;
		entry->next = NULL;
		free(entry);
		return (next);
	}
	return (NULL);
}

int					lst_rm_data(t_lst *lst, f_equal equal, pointer data)
{
	t_node			*node;

	node = lst->first;
	while (node)
	{
		if (equal(node->data, data))
		{
			node = ft_node_del(node, NULL);
			if (node == lst->first)
				lst->first = lst->first->next;
			if (node == lst->last)
				lst->last = lst->last->prev;
			lst->length--;
			node->prev = NULL;
			node->next = NULL;
			free(node);
			return (1);
		}
		node = node->next;
	}
	return (0);
}

int					lst_contains(t_lst *lst, f_equal equal, pointer data)
{
	size_t			i;
	t_node			*node;

	i = 0;
	node = lst->first;
	while  (i < lst->length) {
		if (equal(node->data, data))
			return (1);
		i++;
		node = node->next;
	}
	return (0);
}

t_node *lst_find_data(t_node *lst,
                          f_equal callback, pointer data)
{
	t_node *rover;
	for (rover=lst; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}
	return NULL;
}

void lst_foreach(t_lst *lst, f_map merge_func)
{
	ft_lstiter(lst->first, (void (*)(t_node *)) merge_func);
}

t_itr			*lst_itr_load(t_lst *lst, t_itr *itr, f_prdct prdct)
{
	size_t 		i;
	t_node		*entry;

	itr_clear(itr);
	if (!itr && !(itr = ft_memalloc(sizeof(t_itr))))
			return (NULL);
	entry = lst->last;
	i = 0;
	while (i++ < lst->length)
	{
		if (!prdct || prdct(entry->data))
			ft_node_prepend(&itr->_cur_node, entry->data);
		entry = entry->prev;
	}
	itr->_start_node = itr->_cur_node;
	return (itr);
}

