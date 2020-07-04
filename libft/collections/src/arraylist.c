/*

Copyright (c) 2005-2008, Simon Howard

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

 */

#include <stdlib.h>
#include <string.h>

#include "../includes/arraylist.h"

/* malloc() / free() testing */

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

# define DEF_SIZE 16

/* Automatically resizing array */

t_alist *alist_new(size_t length)
{
	t_alist *new;

	length = length ? length : DEF_SIZE;
	if (!(new = (t_alist *) malloc(sizeof(t_alist))) ||
		(!(new->data = ft_tmalloc(sizeof(pointer), length))))
	{
		new && ft_free(new->data) && ft_free(new);
		return (NULL);
	}
	new->_alloced = length;
	new->length = 0;

	return new;
}

void alist_free(t_alist *arraylist)
{
	if (arraylist)
		free(arraylist->data);
	free(arraylist);
}

static int arraylist_enlarge(t_alist *arraylist)
{
	pointer *data;
	size_t newsize;

	newsize = arraylist->_alloced * 2;
	if (!(data = ft_tmemalloc(sizeof(pointer), newsize)))
		return (0);
	memcpy(data, arraylist->data, arraylist->length * sizeof(pointer));
	arraylist->data = data;
	arraylist->_alloced = newsize;
	return (1);
}

int alist_insert(t_alist *arraylist, size_t index, pointer data)
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

int alist_append(t_alist *arraylist, pointer data)
{
	return alist_insert(arraylist, arraylist->length, data);
}

int alist_prepend(t_alist *arraylist, pointer data)
{
	return alist_insert(arraylist, 0, data);
}

void alist_remove_range(t_alist *arraylist, size_t index,
						size_t length)
{
	/* Check this is a valid range */

	if (index > arraylist->length || index + length > arraylist->length) {
		return;
	}

	/* Move back the entries following the range to be removed */

	memmove(&arraylist->data[index],
	        &arraylist->data[index + length],
	        (arraylist->length - (index + length))
	            * sizeof(pointer));

	/* Decrease the counter */

	arraylist->length -= length;
}

void alist_remove(t_alist *arraylist, size_t index)
{
	alist_remove_range(arraylist, index, 1);
}

int alist_index_of(t_alist *arraylist,
				   is_equal callback,
				   pointer data)
{
	size_t i;

	for (i=0; i<arraylist->length; ++i) {
		if (callback(arraylist->data[i], data) != 0)
			return (int) i;
	}

	return -1;
}

void alist_clear(t_alist *arraylist)
{
	/* To clear the list, simply set the length to zero */

	arraylist->length = 0;
}

static void arraylist_sort_internal(pointer *list_data,
									size_t list_length,
									compare compare_func)
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

void arraylist_sort(t_alist *arraylist, compare compare_func)
{
	/* Perform the recursive sort */

	arraylist_sort_internal(arraylist->data, arraylist->length,
	                        compare_func);
}

