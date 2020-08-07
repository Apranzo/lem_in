/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:24 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 15:06:24 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

#include <coreft.h>
#include <libft/collections/includes/list.h>

typedef pointer				que_val;

typedef struct				s_queue_entry
{
	que_val					data;
	struct s_queue_entry	*prev;
	struct s_queue_entry	*next;
}							t_qu_entry;

typedef struct 				s_queue
{
	t_qu_entry				*head;
	t_qu_entry				*tail;
	size_t					len;
}							t_qu;

/**
 * Create a new double-ended queue.
 *
 * @return           A new queue, or NULL if it was not possible to allocate
 *                   the memory.
 */

t_qu						*qu_by_lst(t_lst *lst);
int							qu_contains(t_qu *qu, que_val data);
t_qu						*qu_new(void);
void						qu_free(t_qu *queue);
void						qu_clear(t_qu *queue);
int							qu_push_head(t_qu *queue, que_val data);
que_val						qu_pop_head(t_qu *queue);
que_val						qu_peek_head(t_qu *queue);
int							qu_push_tail(t_qu *queue, que_val data);
que_val						qu_pop_tail(t_qu *queue);
que_val						qu_peek_tail(t_qu *queue);
int							qu_is_empty(t_qu *queue);

#endif

