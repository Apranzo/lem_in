/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:06:47 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_itr			*lst_itr_load(t_lst *lst, t_itr *itr, t_fprdct prdct)
{
	size_t		i;
	t_node		*entry;

	itr_clear(itr);
	if (!itr && !(itr = ft_memalloc(sizeof(t_itr))))
		return (NULL);
	entry = lst->last;
	i = 0;
	while (i++ < lst->length)
	{
		if (!prdct || prdct(entry->data))
			ft_node_prepend(&itr->cur_node, entry->data);
		entry = entry->prev;
	}
	itr->start_node = itr->cur_node;
	return (itr);
}

t_pntr			*lst_to_array(t_lst *lst)
{
	t_node		*rover;
	t_pntr		*array;
	size_t		i;

	if (!(array = ft_tmalloc(sizeof(t_pntr), lst->length + 1)))
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
