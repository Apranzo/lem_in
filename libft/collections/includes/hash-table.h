#ifndef HASH_MAP_H
# define HASH_MAP_H

#include <coreft.h>
#include <iterator.h>
#include "list.h"

typedef void				(*hm_free_key)(pointer value);
typedef void				(*hm_free_val)(pointer value);


typedef struct				s_hash_map_entry
{
	t_pair					pair;
	struct s_hash_map_entry *next;
}							t_hm_entry;

typedef struct				s_hash_map
{
	t_hm_entry				**table;
	t_lst					values;
	size_t					table_size;
	f_hash					hash_func;
	f_equal					equal_func;
	hm_free_key				free_key;
	hm_free_val				free_val;
	size_t					entries;
	size_t					prime_index;
}							t_hash_map;

t_lst						*hm_lst(t_hash_map *hash_map, f_prdct prdct);
void						hm_clear(t_hash_map *hash_map);
t_hash_map					*hm_init(t_hash_map  *map, f_hash hash_func,
									   f_equal equal_func);
t_hash_map					*hm_new(f_hash hash_func,
									  f_equal equal_func);
void						hm_free(t_hash_map *hash_map,
										f_free free_key, f_free free_val);
void						hm_register_free_functions(t_hash_map *hash_map,
														hm_free_key key_free_func,
														hm_free_val value_free_func);
int							hm_insert(t_hash_map *hash_map,
											   pointer key,
											   pointer value);
pointer						hm_lookup(t_hash_map *hash_map,
											   pointer key);
int							hm_remove(t_hash_map *hash_map, pointer key);
size_t						hm_num_entries(t_hash_map *hash_map);
t_itr						*hm_itr_load(t_hash_map *hash_map,  t_itr *itr);
//t_pair					itr_next(t_itr *iterator);

#endif
