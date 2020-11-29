/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_push_pop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:53:41 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

int				qu_push_tail(t_qu *qu, t_pntr data)
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

t_pntr			qu_pop_tail(t_qu *qu)
{
	t_qu_entry	*entry;
	t_pntr		result;

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

int				qu_push_head(t_qu *qu, t_pntr data)
{
	t_qu_entry	*node;

	if (!qu || !(node = malloc(sizeof(t_qu_entry))))
		return (0);
	node->data = data;
	node->prev = NULL;
	node->next = qu->head;
	if (!qu->head)
	{
		qu->head = node;
		qu->tail = node;
	}
	else
	{
		qu->head->prev = node;
		qu->head = node;
	}
	qu->len++;
	return (1);
}

t_pntr			qu_pop_head(t_qu *qu)
{
	t_qu_entry	*entry;
	t_pntr		result;

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
	return (result);
}
