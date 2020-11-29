/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:56:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void			lst_clear(t_lst *lst, t_ffree free_data)
{
	t_node		*entry;
	t_node		*next;

	if (lst)
	{
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
}

void			lst_free(t_lst *lst, t_ffree free_data)
{
	lst_clear(lst, free_data);
	free(lst);
}

t_lst			*lst_new(void)
{
	return (ft_memalloc(sizeof(t_lst)));
}

int				lst_contains(t_lst *lst, t_fequal equal, t_pntr data)
{
	size_t		i;
	t_node		*node;

	i = 0;
	node = lst->first;
	while (i < lst->length)
	{
		if (equal(node->data, data))
			return (1);
		i++;
		node = node->next;
	}
	return (0);
}

void			lst_foreach(t_lst *lst, t_fmap merge_func)
{
	ft_lstiter(lst->first, (void (*)(t_node *)) merge_func);
}
