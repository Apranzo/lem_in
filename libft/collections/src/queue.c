
#include "queue.h"

/* malloc() / free() testing */


/* A double-ended queue */


t_qu *qu_new(void)
{
	t_qu *qu;

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

void qu_free(t_qu *qu)
{
	qu_clear(qu);
	free(qu);
}

void qu_clear(t_qu *qu)
{
	while (!qu_is_empty(qu))
		qu_pop_head(qu);
}

int qu_push_head(t_qu *qu, que_val data)
{
	t_qu_entry *node;

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

que_val qu_pop_head(t_qu *qu)
{
	t_qu_entry *entry;
	que_val result;

	/* Check the qu is not empty */

	if (qu_is_empty(qu)) {
		return NULL;
	}

	/* Unlink the first entry from the head of the qu */

	entry = qu->head;
	qu->head = entry->next;
	result = entry->data;

	if (qu->head == NULL) {

		/* If doing this has unlinked the last entry in the qu, set
		 * tail to NULL as well. */

		qu->tail = NULL;
	} else {

		/* The new first in the qu has no previous entry */

		qu->head->prev = NULL;
	}

	/* Free back the qu entry structure */

	free(entry);

	qu->len--;
	return result;
}

que_val qu_peek_head(t_qu *qu)
{
	return (!qu_is_empty(qu) ? qu->head->data : NULL);
}

int qu_contains(t_qu *qu, que_val data)
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

int qu_push_tail(t_qu *qu, que_val data)
{
	t_qu_entry *new_entry;

	/* Create the new entry and fill in the fields in the structure */

	new_entry = malloc(sizeof(t_qu_entry));

	if (new_entry == NULL) {
		return 0;
	}

	new_entry->data = data;
	new_entry->prev = qu->tail;
	new_entry->next = NULL;

	/* Insert into the qu tail */

	if (qu->tail == NULL) {

		/* If the qu was previously empty, both the head and
		 * tail must be pointed at the new entry */

		qu->head = new_entry;
		qu->tail = new_entry;

	} else {

		/* The current entry at the tail must have next pointed to this
		 * new entry */

		qu->tail->next = new_entry;

		/* Only the tail must be pointed at the new entry */

		qu->tail = new_entry;
	}
	qu->len++;
	return 1;
}

que_val qu_pop_tail(t_qu *qu)
{
	t_qu_entry *entry;
	que_val result;

	/* Check the qu is not empty */

	if (qu_is_empty(qu)) {
		return NULL;
	}

	/* Unlink the first entry from the tail of the qu */

	entry = qu->tail;
	qu->tail = entry->prev;
	result = entry->data;

	if (qu->tail == NULL) {

		/* If doing this has unlinked the last entry in the qu, set
		 * head to NULL as well. */

		qu->head = NULL;

	} else {

		/* The new entry at the tail has no next entry. */

		qu->tail->next = NULL;
	}

	/* Free back the qu entry structure */

	free(entry);

	qu->len--;
	return result;
}

que_val qu_peek_tail(t_qu *qu)
{
	if (qu_is_empty(qu)) {
		return NULL;
	} else {
		return qu->tail->data;
	}
}

int qu_is_empty(t_qu *qu)
{
	return (!qu->head);
}

