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

/**
 * @file arraylist.h
 *
 * @brief Automatically resizing array
 *
 * ArrayLists are arrays of pointers which automatically increase in
 * size.
 *
 * To create an t_alist, use @ref alist_new.
 * To destroy an t_alist, use @ref arraylist_free.
 *
 * To add a pointer to an t_alist, use @ref alist_prepend,
 * @ref arraylist_append, or @ref alist_insert.
 *
 * To remove a pointer from an t_alist, use @ref alist_remove
 * or @ref alist_remove_range.
 */

#ifndef ALGORITHM_ARRAYLIST_H
# define ALGORITHM_ARRAYLIST_H

#include <coreft.h>


typedef int			(*is_equal)(pointer value1,
								   pointer value2);

typedef int			(*compare)(pointer value1,
								  pointer value2);

typedef struct 		s_alist
{
	pointer			*data;
	size_t			length;
	size_t			_alloced;
	is_equal 		_equal_val;
	compare 		_comp_val;
}					t_alist;


t_alist				*alist_new(size_t length, is_equal, compare);
void				alist_free(t_alist *arraylist);
int					alist_append(t_alist *arraylist, pointer data);
int					alist_prepend(t_alist *arraylist, pointer data);
void				alist_remove(t_alist *arraylist, size_t index);
void				alist_remove_range(t_alist *arraylist, size_t index,
						size_t length);
int					alist_insert(t_alist *arraylist, size_t index,
									pointer data);
size_t				alist_index_of(t_alist *arraylist, is_equal callback,
									  pointer data);
int					alist_contains(t_alist *arraylist, is_equal callback,
									  pointer data);
void				alist_clear(t_alist *arraylist);
void				arraylist_sort(t_alist *arraylist, compare compare_func);

#endif

