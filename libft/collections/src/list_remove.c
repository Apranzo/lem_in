/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:06:38 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_node			*lst_rm_entry(t_lst *lst, t_node *entry)
{
	t_node		*next;

	if ((entry = ft_node_del(entry, NULL)))
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

int				lst_rm_data(t_lst *lst, t_fequal equal, t_pntr data)
{
	t_node		*node;

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
