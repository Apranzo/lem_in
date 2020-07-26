#ifndef ITERATOR_H
# define ITERATOR_H

#include <coreft.h>

//typedef struct s_iterator 	t_itr;

//typedef pointer 			(*f_itr_next)(t_itr *itr);
//typedef void				(*f_itr_reset)(t_itr* itr);

//typedef union 				s_iterator_value
//{
//	pointer 		blob;
//	t_pair 			*key_val;
//}					t_itr_val;

typedef struct 				s_iterator
{
	pointer 				collection;
	t_node 					*_cur_node;
	t_node 					*_start_node;
//	size_t					next_chain;
//	f_itr_next				f_next;
//	f_itr_reset 			f_reset;
}							t_itr;

void					itr_reset(t_itr *itr);
void 					itr_free(t_itr *itr);
void					itr_clear(t_itr *itr);
pointer					itr_next(t_itr *iterator);
int 					itr_has_more(t_itr *itr);

void		itr_foreach(t_itr *iter, void (*f)(pointer data));

#endif //LEM_IN_ITERATOR_H
