#ifndef HASH_MAP_H
# define HASH_MAP_H

#include <coreft.h>
#include <iterator.h>

typedef size_t				(*hm_hash_f)(pointer value);
typedef int					(*hm_equal_f)(pointer value1, pointer value2);
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
	size_t					table_size;
	hm_hash_f				hash_func;
	hm_equal_f				equal_func;
	hm_free_key				free_key;
	hm_free_val				free_val;
	size_t					entries;
	size_t					prime_index;
}							t_hash_map;


void						hm_clear(t_hash_map *hash_map);
t_hash_map					*hm_init(t_hash_map  *map, hm_hash_f hash_func,
											 hm_equal_f equal_func);
t_hash_map					*hm_new(hm_hash_f hash_func,
											hm_equal_f equal_func);
void						hm_free(t_hash_map *hash_map);
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
int							hm_iter_has_more(t_itr *iterator);
//t_hm_pair					hm_iter_next(t_itr *iterator);

#endif
