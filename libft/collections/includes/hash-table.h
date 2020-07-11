#ifndef HASH_MAP_H
# define HASH_MAP_H

#include <coreft.h>

typedef pointer				hm_key;
typedef pointer				hm_val;

typedef size_t				(*hm_hash_f)(hm_key value);
typedef int					(*hm_equal_f)(hm_key value1, hm_key value2);
typedef void				(*hm_free_key)(hm_key value);
typedef void				(*hm_free_val)(hm_val value);

typedef struct				s_hm_pair
{
	hm_key					key;
	hm_val					value;
}							t_hm_pair;

typedef struct				s_hash_map_entry
{
	t_hm_pair				pair;
	struct s_hash_map_entry *next;
}							t_hm_entry;

typedef struct				s_hash_map
{
	t_hm_entry				**table;
	size_t					table_size;
	hm_hash_f				hash_func;
	hm_equal_f				equal_func;
	hm_free_key				free_key;
	hm_free_val				free_val;
	size_t					entries;
	size_t					prime_index;
}							t_hash_map;

typedef struct 				s_hm_iterator
{
	t_hash_map				*hash_map;
	t_node 					*_cur_node;
	size_t					next_chain;
}							t_itr;

t_hash_map					*hash_map_init(t_hash_map  *map, hm_hash_f hash_func,
											 hm_equal_f equal_func);
t_hash_map					*hash_map_new(hm_hash_f hash_func,
											hm_equal_f equal_func);
void						hash_map_free(t_hash_map *hash_map);
void						hash_map_register_free_functions(t_hash_map *hash_map,
														hm_free_key key_free_func,
														hm_free_val value_free_func);
int							hash_map_insert(t_hash_map *hash_map,
												hm_key key,
					  							hm_val value);
hm_val						hash_map_lookup(t_hash_map *hash_map,
						 						hm_key key);
int							hash_map_remove(t_hash_map *hash_map, hm_key key);
size_t						hash_map_num_entries(t_hash_map *hash_map);
void						hash_map_iterate(t_hash_map *hash_map,
											 t_itr *itr);
int							hash_map_iter_has_more(t_itr *iterator);
t_hm_pair					hash_map_iter_next(t_itr *iterator);

#endif
