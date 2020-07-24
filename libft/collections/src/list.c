#include <stdlib.h>

#include "list.h"

/* malloc() / free() testing */

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

/* A doubly-linked lst */


void lst_free(t_lst *lst)
{
	t_node *entry;
	t_node *next;

	entry = lst->first;
	while (entry)
	{
		next = entry->next;
		free(entry);
		entry = next;
	}
	lst->length = 0;
}

t_node *lst_prepend(t_lst *lst, pointer data)
{
	t_node			*new;

	if (!lst || !(new = ft_node_prepend(&lst->first, data)))
		return (NULL);
	lst->length++;
	return (new);
}

t_node *lst_append(t_lst *lst, pointer data)
{
	t_node			*new;

	if (!lst || !(new = ft_node_append(&lst->last, data)))
		return (NULL);
	if (!lst->length)
		lst->first = new;
	lst->last = new;
	lst->length++;
	return (new);
}

//pointer lst_data(t_node *t_node)
//{
//	if (t_node == NULL) {
//		return lst_NULL;
//	}
//
//	return t_node->data;
//}

//void lst_set_data(t_node *t_node, pointer value)
//{
//	if (t_node != NULL) {
//		t_node->data = value;
//	}
//}

//t_node *lst_prev(t_node *t_node)
//{
//	if (t_node == NULL) {
//		return NULL;
//	}
//
//	return t_node->prev;
//}

//t_node *lst_next(t_node *t_node)
//{
//	if (t_node == NULL) {
//		return NULL;
//	}
//
//	return t_node->next;
//}

t_lst				*lst_new()
{
	return (ft_memalloc(sizeof(t_lst)));
}

t_node				*lst_nth_entry(t_lst *lst, size_t index)
{
	t_node			*entry;
	size_t			i;

	i = 0;
	entry = NULL;
	if (lst->length / 2 > index)
	{
		entry = lst->first;
		while (i++ < index)
			entry = entry->next;
	}
	else if(lst->length > index)
	{
		entry = lst->last;
		while (i++ < lst->length - index - 1)
			entry = entry->prev;
	}
	return (entry);
}

pointer			lst_nth_data(t_lst *lst, size_t index)
{
	t_node		*entry;

	entry = lst_nth_entry(lst, index);
	return (entry ? entry->data : NULL);
}

//size_t lst_length(t_node *lst)
//{
//	t_node *entry;
//	size_t length;
//
//	length = 0;
//	entry = lst;
//
//	while (entry != NULL) {
//
//		/* Count the number of entries */
//
//		++length;
//
//		entry = entry->next;
//	}
//
//	return length;
//}

pointer				*lst_to_array(t_lst *lst)
{
	t_node			*rover;
	pointer			*array;
	size_t			i;

	if (!(array = ft_tmalloc(sizeof(pointer),  lst->length + 1)))
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

int lst_remove_entry(t_lst *lst, t_node *entry)
{
	if((entry = ft_node_del(entry, NULL)))
	{
		if (entry == lst->first)
			lst->first = lst->first->next;
		if (entry == lst->last)
			lst->last = lst->last->prev;
//		free(entry);
		lst->length--;
		return (1);
	}
	return (0);
//	/* If the lst is empty, or entry is NULL, always fail */
//
//	if (lst == NULL || *lst == NULL || entry == NULL) {
//		return 0;
//	}
//
//	/* Action to take is different if the entry is the first in the lst */
//
//	if (entry->prev == NULL) {
//
//		/* Unlink the first entry and update the starting pointer */
//
//		*lst = entry->next;
//
//		/* Update the second entry's prev pointer, if there is a second
//		 * entry */
//
//		if (entry->next != NULL) {
//			entry->next->prev = NULL;
//		}
//
//	} else {
//
//		/* This is not the first in the lst, so we must have a
//		 * previous entry.  Update its 'next' pointer to the new
//		 * value */
//
//		entry->prev->next = entry->next;
//
//		/* If there is an entry following this one, update its 'prev'
//		 * pointer to the new value */
//
//		if (entry->next != NULL) {
//			entry->next->prev = entry->prev;
//		}
//	}
//
//	/* Free the lst entry */
//
//	free(entry);
//
//	/* Operation successful */
//
//	return 1;
}
//
//size_t	 lst_remove_data(t_node **lst, f_equal callback,
//                              pointer data)
//{
//	size_t entries_removed;
//	t_node *rover;
//	t_node *next;
//
//	if (lst == NULL || callback == NULL) {
//		return 0;
//	}
//
//	entries_removed = 0;
//
//	/* Iterate over the entries in the lst */
//
//	rover = *lst;
//
//	while (rover != NULL) {
//
//		next = rover->next;
//
//		if (callback(rover->data, data)) {
//
//			/* This data needs to be removed.  Unlink this entry
//			 * from the lst. */
//
//			if (rover->prev == NULL) {
//
//				/* This is the first entry in the lst */
//
//				*lst = rover->next;
//			} else {
//
//				/* Point the previous entry at its new
//				 * location */
//
//				rover->prev->next = rover->next;
//			}
//
//			if (rover->next != NULL) {
//				rover->next->prev = rover->prev;
//			}
//
//			/* Free the entry */
//
//			free(rover);
//
//			++entries_removed;
//		}
//
//		/* Advance to the next lst entry */
//
//		rover = next;
//	}
//
//	return entries_removed;
//}

/* Function used internally for sorting.  Returns the last entry in the
 * new sorted lst */

static t_node *lst_sort_internal(t_node **node,
                                     f_compare compare_func)
{
	t_node *pivot;
	t_node *rover;
	t_node *less_lst;
	t_node *more_lst;
	t_node *less_lst_end, *more_lst_end;

	if (!node || !compare_func)
		return (NULL);
	if (!*node || !(*node)->next)
		return (*node);

	/* The first entry is the pivot */

	pivot =	*node;

	/* Iterate over the lst, starting from the second entry.  Sort
	 * all entries into the less and more lsts based on comparisons
	 * with the pivot */

	less_lst = NULL;
	more_lst = NULL;
	rover = pivot->next;

	while (rover)
	{
		t_node *next = rover->next;
		if (compare_func(rover->data, pivot->data) < 0)
		{

			/* Place this in the less lst */

			rover->prev = NULL;
			rover->next = less_lst;
			if (less_lst)
				less_lst->prev = rover;
			less_lst = rover;

		}
		else
		{

			/* Place this in the more lst */

			rover->prev = NULL;
			rover->next = more_lst;
			if (more_lst)
				more_lst->prev = rover;
			more_lst = rover;
		}
		rover = next;
	}

	/* Sort the sublsts recursively */

	less_lst_end = lst_sort_internal(&less_lst, compare_func);
	more_lst_end = lst_sort_internal(&more_lst, compare_func);

	/* Create the new lst starting from the less lst */

	*node = less_lst;

	/* Append the pivot to the end of the less lst.  If the less lst
	 * was empty, start from the pivot */

	if (!less_lst)
	{
		pivot->prev = NULL;
		*node = pivot;
	}
	else
	{
		pivot->prev = less_lst_end;
		less_lst_end->next = pivot;
	}

	/* Append the more lst after the pivot */

	pivot->next = more_lst;
	if (more_lst)
		more_lst->prev = pivot;
	/* Work out what the last entry in the lst is.  If the more lst was
	 * empty, the pivot was the last entry.  Otherwise, the end of the
	 * more lst is the end of the total lst. */
	return (!more_lst ? pivot : more_lst_end);

//	if (more_lst) {
//		return pivot;
//	} else {
//		return more_lst_end;
//	}
}

void lst_sort(t_lst *lst, f_compare compare_func)
{
	lst->last = lst_sort_internal(&lst->first, compare_func);
}

t_node *lst_find_data(t_node *lst,
                          f_equal callback,
                          pointer data)
{
	t_node *rover;

	/* Iterate over entries in the lst until the data is found */

	for (rover=lst; rover != NULL; rover=rover->next) {
		if (callback(rover->data, data) != 0) {
			return rover;
		}
	}

	/* Not found */

	return NULL;
}

void lst_foreach(t_lst *lst, f_map merge_func)
{
	ft_lstiter(lst->first, (void (*)(t_node *)) merge_func);
}

t_itr			*lst_itr_load(t_lst *lst, t_itr *itr, f_prdct prdct)
{
	size_t 		i;
	t_node		*entry;

	if (!itr && !(itr = ft_memalloc(sizeof(t_itr))))
			return (NULL);
	itr_clear(itr);
	itr->collection = lst;
	entry = lst->last;
	i = 0;
	while (i++ < lst->length)
	{
		if (!prdct || prdct(entry->data))
			ft_node_prepend(&itr->_cur_node, entry->data);
		entry = entry->prev;
	}
	return (itr);
}

