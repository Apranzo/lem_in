#ifndef hash_map_H
#define hash_map_H

#include <libft.h>

typedef pointer				hm_key;
typedef pointer				hm_val;


typedef size_t				(*hash_func)(hm_key value);
typedef int					(*hm_is_equal)(hm_key value1, hm_key value2);
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
	hash_func				hash_func;
	hm_is_equal				equal_func;
	hm_free_key				free_key;
	hm_free_val				free_val;
	size_t					entries;
	size_t					prime_index;
}							t_hash_map;

typedef struct 				s_hm_iterator
{
	t_hash_map				*hash_map;
	t_hm_entry				*next_entry;
	size_t					next_chain;
}							t_hm_iterator;

t_hash_map					*hash_map_new(hash_func hash_func,
											hm_is_equal equal_func);
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
												t_hm_iterator *iter);
int							hash_map_iter_has_more(t_hm_iterator *iterator);
t_hm_pair					hash_map_iter_next(t_hm_iterator *iterator);

#endif

