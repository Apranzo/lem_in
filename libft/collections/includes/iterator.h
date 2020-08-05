#ifndef ITERATOR_H
# define ITERATOR_H

#include <coreft.h>

typedef struct 				s_iterator
{
//	pointer 				collection;
	t_node 					*_cur_node;
	t_node 					*_start_node;
}							t_itr;

void					itr_reset(t_itr *itr);
void 					itr_free(t_itr *itr);
void					itr_clear(t_itr *itr);
pointer					itr_next(t_itr *iterator);
int 					itr_has_more(t_itr *itr);

void		itr_foreach(t_itr *iter, void (*f)(pointer data));

#endif //LEM_IN_ITERATOR_H
