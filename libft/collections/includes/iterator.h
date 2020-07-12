#ifndef ITERATOR_H
# define ITERATOR_H

#include <coreft.h>

typedef pointer 			(*f_itr_next)(t_itr* itr);
//typedef void				(*f_itr_reset)(t_itr* itr);

struct 						s_iterator
{
	pointer 				collection;
	t_node 					*_cur_node;
//	size_t					next_chain;
	f_itr_next				f_next;
//	f_itr_reset 			f_reset;
};

void					itr_clear(t_itr *itr);

#endif //LEM_IN_ITERATOR_H
