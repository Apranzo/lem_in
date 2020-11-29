/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:06:44 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_pntr			lst_nth_data(t_lst *lst, size_t index)
{
	t_node		*entry;

	entry = lst_nth_entry(lst, index);
	return (entry ? entry->data : NULL);
}

t_node			*lst_nth_entry(t_lst *lst, size_t index)
{
	t_node		*entry;
	size_t		i;

	i = 0;
	entry = NULL;
	if (lst->length / 2 > index)
	{
		entry = lst->first;
		while (i++ < index)
			entry = entry->next;
	}
	else if (lst->length > index)
	{
		entry = lst->last;
		while (i++ < lst->length - index - 1)
			entry = entry->prev;
	}
	return (entry);
}
