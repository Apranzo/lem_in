#ifndef QUEUE_H
# define QUEUE_H

#include <coreft.h>

typedef pointer				que_val;

typedef struct				s_queue_entry
{
	que_val data;
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

int							queue_contains(t_qu *qu, que_val data);
t_qu						*queue_new(void);
void						queue_free(t_qu *queue);
void						queue_clear(t_qu *queue);
int							queue_push_head(t_qu *queue, que_val data);
que_val						queue_pop_head(t_qu *queue);
que_val						queue_peek_head(t_qu *queue);
int							queue_push_tail(t_qu *queue, que_val data);
que_val						queue_pop_tail(t_qu *queue);
que_val						queue_peek_tail(t_qu *queue);
int							queue_is_empty(t_qu *queue);

#endif

