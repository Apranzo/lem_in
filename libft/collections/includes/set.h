#ifndef SET_H
# define SET_H

#include <coreft.h>

typedef pointer				set_val;

typedef size_t				(*set_hash_f)(set_val value);
typedef void				(*set_free_val)(set_val value);
typedef int					(*set_equal_f)(set_val value1, set_val value2);

typedef struct				s_set_entry
{
	set_val					data;
	struct s_set_entry		*next;
}							t_set_entry;

typedef struct				s_set
{
	t_set_entry				**table;
	size_t 					entries;
	size_t					table_size;
	size_t 					prime_index;
	set_hash_f				hash_func;
	set_equal_f				equal_func;
	set_free_val			free_func;
}							t_set;

typedef struct				s_set_iteratos
{
	t_set					*set;
	t_set_entry				*next_entry;
	size_t 					next_chain;
}							t_set_iter;



t_set						*set_init(t_set *set, set_hash_f hash_func, set_equal_f equal_func);
t_set						*set_new(set_hash_f hash_func, set_equal_f equal_func);
void						set_free(t_set *set);
void						set_register_free_function(t_set *set, set_free_val free_func);
int							set_insert(t_set *set, set_val data);
int							set_remove(t_set *set, set_val data);
int							set_query(t_set *set, set_val data);
size_t						set_num_entries(t_set *set);
set_val						*set_to_array(t_set *set);
t_set						*set_union(t_set *set1, t_set *set2);
t_set						*set_intersection(t_set *set1, t_set *set2);
void						set_iterate(t_set *set, t_set_iter *iter);
int							set_iter_has_more(t_set_iter *iterator);
set_val						set_iter_next(t_set_iter *iterator);

#endif
