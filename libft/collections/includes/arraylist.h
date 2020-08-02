#ifndef ARRAYLIST_H
# define ARRAYLIST_H

#include <coreft.h>
#include <iterator.h>


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
//	is_equal 		_equal_val;
//	compare 		_comp_val;
}					t_alst;


t_alst				*alst_new(size_t length, f_equal, f_compare);
t_alst				*alst_init(t_alst *list, size_t length, f_equal, f_compare);
void				alst_free(t_alst *alst);
int					alst_append(t_alst *alst, pointer data);
int					alst_prepend(t_alst *alst, pointer data);
void				alst_remove(t_alst *alst, size_t index);
void				alst_remove_range(t_alst *alst, size_t index,
									   size_t length);
int					alst_insert(t_alst *alst, size_t index,
									pointer data);
size_t				alst_index_of(t_alst *alst, f_equal callback,
									 pointer data);
int					alst_contains(t_alst *alst, f_equal equal, pointer data);
void				alst_clear(t_alst *alst);
void				alst_sort(t_alst *alst, f_compare compare_func);

#endif

