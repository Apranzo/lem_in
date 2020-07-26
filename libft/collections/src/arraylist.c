#include <stdlib.h>
#include <string.h>

#include "../includes/arraylist.h"

/* malloc() / free() testing */
# define DEF_SIZE 16

t_alst *alst_init(t_alst *list, size_t length, f_equal equal, f_compare comp)
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

t_alst *alst_new(size_t length, f_equal equal, f_compare comp)
{
	t_alst *new;

	if (!(new = (t_alst *) ft_memalloc(sizeof(t_alst))))
	{
		ft_free(new);
		return (NULL);
	}
	return (alst_init(new, length, equal, comp));
}


void alst_free(t_alst *alst)
{
	if (alst)
		free(alst->data);
	free(alst);
}

static int alst_enlarge(t_alst *alst)
{
	pointer *data;
	size_t newsize;

	newsize = alst->_alloced * 2;
	if (!(data = ft_memalloc(sizeof(pointer) * newsize)))
		return (0);
	memcpy(data, alst->data, alst->length * sizeof(pointer));
	free(alst->data);
	alst->data = data;
	alst->_alloced = newsize;
	return (1);
}

int alst_insert(t_alst *alst, size_t index, pointer data)
{
	if (index > alst->length ||
			(alst->length + 1 > alst->_alloced &&
				!alst_enlarge(alst)))
			return (0);

	memmove(&alst->data[index + 1],
	        &alst->data[index],
	        (alst->length - index) * sizeof(pointer));

	alst->data[index] = data;
	alst->length++;
	return 1;
}

int alst_append(t_alst *alst, pointer data)
{
	return alst_insert(alst, alst->length, data);
}

int alst_prepend(t_alst *alst, pointer data)
{
	return alst_insert(alst, 0, data);
}

void alst_remove_range(t_alst *alst, size_t index,
						size_t length)
{
	/* Check this is a valid range */

	if (index + length > alst->length)
		return;
	/* Move back the entries following the range to be removed */

	memmove(&alst->data[index],
	        &alst->data[index + length],
	        (alst->length - (index + length))
	            * sizeof(pointer));

	/* Decrease the counter */

	alst->length -= length;
}

void alst_remove(t_alst *alst, size_t index)
{
	alst_remove_range(alst, index, 1);
}

int				alst_contains(t_alst *alst, f_equal callback,
								  pointer data)
{
	return (alst_index_of(alst, callback, data) != alst->length + 1);
}

size_t alst_index_of(t_alst *alst,
					  f_equal callback,
					  pointer data)
{
	size_t i;

//	if (!callback)
//		callback = alst->_equal_val;

	i = 0;
	while  (i < alst->length) {
		if (callback(alst->data[i], data))
			return (i);
		i++;
	}

	return (alst->length + 1);
}

void alst_clear(t_alst *alst)
{
	/* To clear the list, simply set the length to zero */

	alst->length = 0;
}

static void alst_sort_internal(pointer *list_data,
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

	alst_sort_internal(list_data, list1_length, compare_func);

	alst_sort_internal(&list_data[list1_length + 1], list2_length,
	                        compare_func);
}

void alst_sort(t_alst *alst, f_compare compare_func)
{
//	if (!compare_func)
//		compare_func = alst->_comp_val;
	/* Perform the recursive sort */

	alst_sort_internal(alst->data, alst->length,
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

