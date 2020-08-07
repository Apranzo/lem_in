/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash-table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:29:29 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:59:44 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

#include <coreft.h>
#include <iterator.h>
#include "list.h"

static const size_t hm_primes[] = {
		193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
		196613, 393241, 786433, 1572869, 3145739, 6291469,
		12582917, 25165843, 50331653, 100663319, 201326611,
		402653189, 805306457, 1610612741,
};

static const size_t hm_num_primes = sizeof(hm_primes) / sizeof(size_t);

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
	f_hash					hash_func;
	f_equal					equal_func;
	hm_free_key				free_key;
	hm_free_val				free_val;
	size_t					entries;
	size_t					prime_index;
}							t_hm;

t_lst						*hm_lst(t_hm *hash_map, f_prdct prdct);
void						hm_clear(t_hm *hash_map);
t_hm					*hm_init(t_hm  *map, f_hash hash_func,
								 f_equal equal_func);
t_hm					*hm_new(f_hash hash_func,
								f_equal equal_func);
void						hm_free(t_hm *hash_map,
									f_free free_key, f_free free_val);
void						hm_register_free_functions(t_hm *hash_map,
													   hm_free_key key_free_func,
													   hm_free_val value_free_func);
int							hm_insert(t_hm *hm,
										 pointer key,
										 pointer value);
pointer						hm_lookup(t_hm *hm,
										 pointer key);
int							hm_remove(t_hm *hash_map, pointer key);
size_t						hm_num_entries(t_hm *hash_map);
t_itr						*hm_itr_load(t_hm *hash_map, t_itr *itr);
//t_pair					itr_next(t_itr *iterator);

#endif
