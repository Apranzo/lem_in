/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:59 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 15:06:59 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>
#include <iterator.h>

pointer				itr_next(t_itr *iterator)
{
	t_node			*current_entry;
	pointer			data;

	if (!iterator->cur_node)
		return (NULL);
	current_entry = iterator->cur_node;
	iterator->cur_node = current_entry->next;
	data = current_entry->data;
	return (data);
}

int 				itr_has_more(t_itr *itr)
{
	return ((int)itr->cur_node);
}

void					itr_foreach(t_itr *iter, void (*f)(pointer data))
{
	while (itr_has_more(iter))
		f(itr_next(iter));
}

void 					itr_free(t_itr *itr)
{
	itr_clear(itr);
	free(itr);
}

void					itr_clear(t_itr *itr)
{
	t_node				*node;

	if (itr)
	{
		itr_reset(itr);
		node = itr->cur_node;
		while (node)
		{
			itr->cur_node = itr->cur_node->next;
			free(node);
			node = itr->cur_node;
		}
		ft_bzero(itr, sizeof(t_itr));
	}
}

void					itr_reset(t_itr *itr)
{
	itr->cur_node = itr->start_node;
}
