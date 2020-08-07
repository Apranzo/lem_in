/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:07:06 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 15:10:58 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_qu			*qu_new(void)
{
	t_qu		*qu;

	if (!(qu = (t_qu *) malloc(sizeof(t_qu))))
		return (NULL);
	qu->head = NULL;
	qu->tail = NULL;
	qu->len = 0;
	return qu;
}

t_qu			*qu_by_lst(t_lst *lst)
{
	t_qu		*qu;
	t_node		*node;
	size_t		i;

	if (!(qu = qu_new()))
		return (NULL);
	node = lst->first;
	i = 0;
	while (i++ < lst->length)
	{
		if (!(qu_push_head(qu, node->data)))
			return (NULL);
		node = node->next;
	}
	return qu;
}

void			qu_free(t_qu *qu)
{
	qu_clear(qu);
	free(qu);
}

void			qu_clear(t_qu *qu)
{
	while (!qu_is_empty(qu))
		qu_pop_head(qu);
}

int				qu_push_head(t_qu *qu, que_val data)
{
	t_qu_entry	*node;

	if(!qu || !(node = malloc(sizeof(t_qu_entry))))
		return (0);
	node->data = data;
	node->prev = NULL;
	node->next = qu->head;
	if (!qu->head)
	{
		qu->head = node;
		qu->tail = node;

	} else
	{
		qu->head->prev = node;
		qu->head = node;
	}
	qu->len++;
	return (1);
}

que_val			qu_pop_head(t_qu *qu)
{
	t_qu_entry	*entry;
	que_val		result;

	if (qu_is_empty(qu))
		return (NULL);
	entry = qu->head;
	qu->head = entry->next;
	result = entry->data;
	if (!qu->head)
		qu->tail = NULL;
	else
		qu->head->prev = NULL;
	free(entry);
	qu->len--;
	return result;
}

que_val			qu_peek_head(t_qu *qu)
{
	return (!qu_is_empty(qu) ? qu->head->data : NULL);
}

int				qu_contains(t_qu *qu, que_val data)
{
	t_qu_entry	*ent;

	ent = qu->head;
	while (ent)
	{
		if (ent->data == data)
			return (1);
		ent = ent->next;
	}
	return (0);
}

int				qu_push_tail(t_qu *qu, que_val data)
{
	t_qu_entry	*new_entry;

	if (!(new_entry = malloc(sizeof(t_qu_entry))))
		return (0);
	new_entry->data = data;
	new_entry->prev = qu->tail;
	new_entry->next = NULL;
	if (!qu->tail)
	{
		qu->head = new_entry;
		qu->tail = new_entry;
	}
	else
	{
		qu->tail->next = new_entry;
		qu->tail = new_entry;
	}
	qu->len++;
	return (1);
}

que_val			qu_pop_tail(t_qu *qu)
{
	t_qu_entry	*entry;
	que_val		result;

	if (qu_is_empty(qu))
		return (NULL);
	entry = qu->tail;
	qu->tail = entry->prev;
	result = entry->data;

	if (!qu->tail)
		qu->head = NULL;
	else
		qu->tail->next = NULL;
	free(entry);
	qu->len--;
	return (result);
}

que_val			qu_peek_tail(t_qu *qu)
{
	if (qu_is_empty(qu))
		return (NULL);
	return (qu->tail->data);
}

int qu_is_empty(t_qu *qu)
{
	return (!qu->head);
}

