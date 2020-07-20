#include <stdlib.h>
#include <string.h>

#include "../includes/arraylist.h"

/* malloc() / free() testing */
# define DEF_SIZE 16

t_alst *alist_init(t_alst *list, size_t length, f_equal equal, f_compare comp)
{
	length = length > 0 ? length : DEF_SIZE;
	if (!(list->data = ft_memalloc(sizeof(pointer) * length)))
	{
		ft_free(list->data);
		return (NULL);
	}
	list->_alloced = length;
	list->length = 0;
//	list->_equal_val = equal;
//	list->_comp_val = comp;

	return (list);
}

/* Automatically resizing array */

t_alst *alist_new(size_t length, f_equal equal, f_compare comp)
{
	t_alst *new;

	if (!(new = (t_alst *) ft_memalloc(sizeof(t_alst))))
	{
		ft_free(new);
		return (NULL);
	}
	return (alist_init(new, length, equal, comp));
}


void alist_free(t_alst *arraylist)
{
	if (arraylist)
		free(arraylist->data);
	free(arraylist);
}

static int arraylist_enlarge(t_alst *arraylist)
{
	pointer *data;
	size_t newsize;

	newsize = arraylist->_alloced * 2;
	if (!(data = ft_memalloc(sizeof(pointer) * newsize)))
		return (0);
	memcpy(data, arraylist->data, arraylist->length * sizeof(pointer));
	free(arraylist->data);
	arraylist->data = data;
	arraylist->_alloced = newsize;
	return (1);
}

int alist_insert(t_alst *arraylist, size_t index, pointer data)
{
	if (index > arraylist->length ||
			(arraylist->length + 1 > arraylist->_alloced &&
				!arraylist_enlarge(arraylist)))
			return (0);

	memmove(&arraylist->data[index + 1],
	        &arraylist->data[index],
	        (arraylist->length - index) * sizeof(pointer));

	arraylist->data[index] = data;
	arraylist->length++;
	return 1;
}

int alist_append(t_alst *arraylist, pointer data)
{
	return alist_insert(arraylist, arraylist->length, data);
}

int alist_prepend(t_alst *arraylist, pointer data)
{
	return alist_insert(arraylist, 0, data);
}

void alist_remove_range(t_alst *arraylist, size_t index,
						size_t length)
{
	/* Check this is a valid range */

	if (index + length > arraylist->length)
		return;
	/* Move back the entries following the range to be removed */

	memmove(&arraylist->data[index],
	        &arraylist->data[index + length],
	        (arraylist->length - (index + length))
	            * sizeof(pointer));

	/* Decrease the counter */

	arraylist->length -= length;
}

void alist_remove(t_alst *arraylist, size_t index)
{
	alist_remove_range(arraylist, index, 1);
}

int				alist_contains(t_alst *arraylist, f_equal callback,
								  pointer data)
{
	return (alist_index_of(arraylist, callback, data) != arraylist->length + 1);
}

size_t alist_index_of(t_alst *arraylist,
					  f_equal callback,
					  pointer data)
{
	size_t i;

//	if (!callback)
//		callback = arraylist->_equal_val;

	i = 0;
	while  (i < arraylist->length) {
		if (callback(arraylist->data[i], data))
			return (i);
		i++;
	}

	return (arraylist->length + 1);
}

void alist_clear(t_alst *arraylist)
{
	/* To clear the list, simply set the length to zero */

	arraylist->length = 0;
}

static void arraylist_sort_internal(pointer *list_data,
									size_t list_length,
									f_compare compare_func)
{
	pointer pivot;
	pointer tmp;
	size_t i;
	size_t list1_length;
	size_t list2_length;

	/* If less than two items, it is always sorted. */

	if (list_length <= 1) {
		return;
	}

	/* Take the last item as the pivot. */

	pivot = list_data[list_length-1];

	/* Divide the list into two lists:
	 *
	 * List 1 contains data less than the pivot.
	 * List 2 contains data more than the pivot.
	 *
	 * As the lists are build up, they are stored sequentially after
	 * each other, ie. list_data[list1_length-1] is the last item
	 * in list 1, list_data[list1_length] is the first item in
	 * list 2.
	 */

	list1_length = 0;

	for (i=0; i<list_length-1; ++i) {

		if (compare_func(list_data[i], pivot) < 0) {

			/* This should be in list 1.  Therefore it is in the
			 * wrong position. Swap the data immediately following
			 * the last item in list 1 with this data. */

			tmp = list_data[i];
			list_data[i] = list_data[list1_length];
			list_data[list1_length] = tmp;

			++list1_length;

		} else {
			/* This should be in list 2.  This is already in the
			 * right position. */
		}
	}

	/* The length of list 2 can be calculated. */

	list2_length = list_length - list1_length - 1;

	/* list_data[0..list1_length-1] now contains all items which are
	 * before the pivot.
	 * list_data[list1_length..list_length-2] contains all items after
	 * or equal to the pivot. */

	/* Move the pivot into place, by swapping it with the item
	 * immediately following the end of list 1.  */

	list_data[list_length-1] = list_data[list1_length];
	list_data[list1_length] = pivot;

	/* Recursively sort the sublists. */

	arraylist_sort_internal(list_data, list1_length, compare_func);

	arraylist_sort_internal(&list_data[list1_length + 1], list2_length,
	                        compare_func);
}

void arraylist_sort(t_alst *arraylist, f_compare compare_func)
{
//	if (!compare_func)
//		compare_func = arraylist->_comp_val;
	/* Perform the recursive sort */

	arraylist_sort_internal(arraylist->data, arraylist->length,
	                        compare_func);
}

t_itr				*alst_itr_load(t_alst *lst, t_itr *itr)
{
	t_node 			*new;
	t_node 			*tail;
	int 			i;

	if (!lst || !itr)
		return NULL;
	itr_clear(itr);
	i = 0;
	tail = itr->_cur_node;
	while (lst->length < i)
	{
		if (!(new = ft_memalloc(sizeof(t_node))))
			return (NULL);
		new->data = lst->data[i];
		if (!itr->_cur_node)
		{
			itr->_cur_node = new;
			new->prev = itr->_cur_node;
		}
		else
		{
			new->prev = tail;
			tail->next = new;
		}
		tail = new;
		i++;
	}
	return (itr);
}

