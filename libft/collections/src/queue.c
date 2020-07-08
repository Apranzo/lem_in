#include "queue.h"

/* malloc() / free() testing */


/* A double-ended queue */


t_qu *queue_new(void)
{
	t_qu *queue;

	queue = (t_qu *) malloc(sizeof(t_qu));

	if (queue == NULL) {
		return NULL;
	}

	queue->head = NULL;
	queue->tail = NULL;

	return queue;
}

void queue_free(t_qu *queue)
{
	/* Empty the queue */

	while (!queue_is_empty(queue)) {
		queue_pop_head(queue);
	}

	/* Free back the queue */

	free(queue);
}

int queue_push_head(t_qu *queue, que_val data)
{
	t_qu_entry *new_entry;

	/* Create the new entry and fill in the fields in the structure */

	new_entry = malloc(sizeof(t_qu_entry));

	if (new_entry == NULL) {
		return 0;
	}

	new_entry->data = data;
	new_entry->prev = NULL;
	new_entry->next = queue->head;

	/* Insert into the queue */

	if (!queue->head)
	{

		/* If the queue was previously empty, both the head and
		 * tail must be pointed at the new entry */

		queue->head = new_entry;
		queue->tail = new_entry;

	} else {

		/* First entry in the list must have prev pointed back to this
		 * new entry */

		queue->head->prev = new_entry;

		/* Only the head must be pointed at the new entry */

		queue->head = new_entry;
	}

	return (1);
}

que_val queue_pop_head(t_qu *queue)
{
	t_qu_entry *entry;
	que_val result;

	/* Check the queue is not empty */

	if (queue_is_empty(queue)) {
		return NULL;
	}

	/* Unlink the first entry from the head of the queue */

	entry = queue->head;
	queue->head = entry->next;
	result = entry->data;

	if (queue->head == NULL) {

		/* If doing this has unlinked the last entry in the queue, set
		 * tail to NULL as well. */

		queue->tail = NULL;
	} else {

		/* The new first in the queue has no previous entry */

		queue->head->prev = NULL;
	}

	/* Free back the queue entry structure */

	free(entry);

	return result;
}

que_val queue_peek_head(t_qu *queue)
{
	return (!queue_is_empty(queue) ? queue->head->data : NULL);
}

int queue_contains(t_qu *qu, que_val data)
{
	t_qu_entry	*ent;

	ent = qu->head;
	while (ent->next)
	{
		if (ent->data == data)
			return (1);
		ent = ent->next;
	}
}

int queue_push_tail(t_qu *queue, que_val data)
{
	t_qu_entry *new_entry;

	/* Create the new entry and fill in the fields in the structure */

	new_entry = malloc(sizeof(t_qu_entry));

	if (new_entry == NULL) {
		return 0;
	}

	new_entry->data = data;
	new_entry->prev = queue->tail;
	new_entry->next = NULL;

	/* Insert into the queue tail */

	if (queue->tail == NULL) {

		/* If the queue was previously empty, both the head and
		 * tail must be pointed at the new entry */

		queue->head = new_entry;
		queue->tail = new_entry;

	} else {

		/* The current entry at the tail must have next pointed to this
		 * new entry */

		queue->tail->next = new_entry;

		/* Only the tail must be pointed at the new entry */

		queue->tail = new_entry;
	}

	return 1;
}

que_val queue_pop_tail(t_qu *queue)
{
	t_qu_entry *entry;
	que_val result;

	/* Check the queue is not empty */

	if (queue_is_empty(queue)) {
		return NULL;
	}

	/* Unlink the first entry from the tail of the queue */

	entry = queue->tail;
	queue->tail = entry->prev;
	result = entry->data;

	if (queue->tail == NULL) {

		/* If doing this has unlinked the last entry in the queue, set
		 * head to NULL as well. */

		queue->head = NULL;

	} else {

		/* The new entry at the tail has no next entry. */

		queue->tail->next = NULL;
	}

	/* Free back the queue entry structure */

	free(entry);

	return result;
}

que_val queue_peek_tail(t_qu *queue)
{
	if (queue_is_empty(queue)) {
		return NULL;
	} else {
		return queue->tail->data;
	}
}

int queue_is_empty(t_qu *queue)
{
	return queue->head == NULL;
}

