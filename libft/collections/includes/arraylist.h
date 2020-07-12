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

#ifndef ARRAYLIST_H
# define ARRAYLIST_H

#include <coreft.h>
#include <iterator.h>


typedef int			(*is_equal)(pointer value1,
								   pointer value2);

typedef int			(*compare)(pointer value1,
								  pointer value2);

//typedef struct 		s_iterator
//{
//	pointer 		data;
//	t_list			next;
//}					t_iter;

typedef struct 		s_alist
{
	pointer			*data;
	size_t			length;
	size_t			_alloced;
	is_equal 		_equal_val;
	compare 		_comp_val;
}					t_alst;


t_alst				*alist_new(size_t length, is_equal, compare);
t_alst				*alist_init(t_alst *list, size_t length, is_equal, compare);
void				alist_free(t_alst *arraylist);
int					alist_append(t_alst *arraylist, pointer data);
int					alist_prepend(t_alst *arraylist, pointer data);
void				alist_remove(t_alst *arraylist, size_t index);
void				alist_remove_range(t_alst *arraylist, size_t index,
									   size_t length);
int					alist_insert(t_alst *arraylist, size_t index,
									pointer data);
size_t				alist_index_of(t_alst *arraylist, is_equal callback,
									 pointer data);
int					alist_contains(t_alst *arraylist, is_equal callback,
									  pointer data);
void				alist_clear(t_alst *arraylist);
void				arraylist_sort(t_alst *arraylist, compare compare_func);

#endif

