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

/**
 * Add a value to the head of a queue.
 *
 * @param queue      The queue.
 * @param data       The value to add.
 * @return           Non-zero if the value was added successfully, or zero
 *                   if it was not possible to allocate the memory for the
 *                   new entry.
 */
int							queue_push_head(t_qu *queue, que_val data);
/**
 * Remove a value from the head of a queue.
 *
 * @param queue      The queue.
 * @return           Value that was at the head of the queue, or
 *                   @ref QUEUE_NULL if the queue is empty.
 */
que_val						queue_pop_head(t_qu *queue);
/**
 * Read value from the head of a queue, without removing it from
 * the queue.
 *
 * @param queue      The queue.
 * @return           Value at the head of the queue, or @ref QUEUE_NULL if the
 *                   queue is empty.
 */
que_val						queue_peek_head(t_qu *queue);
/**
 * Add a value to the tail of a queue.
 *
 * @param queue      The queue.
 * @param data       The value to add.
 * @return           Non-zero if the value was added successfully, or zero
 *                   if it was not possible to allocate the memory for the
 *                   new entry.
 */
int							queue_push_tail(t_qu *queue, que_val data);
/**
 * Remove a value from the tail of a queue.
 *
 * @param queue      The queue.
 * @return           Value that was at the head of the queue, or
 *                   @ref QUEUE_NULL if the queue is empty.
 */
que_val						queue_pop_tail(t_qu *queue);
/**
 * Read a value from the tail of a queue, without removing it from
 * the queue.
 *
 * @param queue      The queue.
 * @return           Value at the tail of the queue, or QUEUE_NULL if the
 *                   queue is empty.
 */
que_val						queue_peek_tail(t_qu *queue);
int							queue_is_empty(t_qu *queue);

#endif

