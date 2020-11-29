/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash-table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:29:29 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

# include "../../core/includes/coreft.h"
# include "iterator.h"
# include "list.h"

static const size_t			g_hm_primes[] = {
	193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
	196613, 393241, 786433, 1572869, 3145739, 6291469,
	12582917, 25165843, 50331653, 100663319, 201326611,
	402653189, 805306457, 1610612741
};

static const size_t			g_hm_num_primes =
sizeof(g_hm_primes) / sizeof(size_t);
typedef void				(*t_hm_free_key)(t_pntr value);
typedef void				(*t_hm_free_val)(t_pntr value);
typedef struct				s_hash_map_entry
{
	t_pair					pair;
	struct s_hash_map_entry *next;
}							t_hm_entry;

typedef struct				s_hash_map
{
	t_hm_entry				**table;
	size_t					table_size;
	t_fhash					hash_func;
	t_fequal				equal_func;
	t_hm_free_key			free_key;
	t_hm_free_val			free_val;
	size_t					entries;
	size_t					prime_index;
}							t_hm;

void						hm_free_entry(t_hm *hash_map,
								t_hm_entry *entry);
int							hm_enlarge(t_hm *hm);
t_lst						*hm_lst(t_hm *hash_map, t_fprdct prdct);
t_hm						*hm_clear(t_hm *hash_map);
t_hm						*hm_init(t_hm *map, t_fhash hash_func,
									t_fequal equal_func);
t_hm						*hm_new(t_fhash hash_func,
									t_fequal equal_func);
void						hm_free(t_hm *hash_map,
									t_ffree free_key, t_ffree free_val);
void						hm_register_free_functions(t_hm *hash_map,
												t_hm_free_key key_free_func,
												t_hm_free_val value_free_func);
int							hm_insert(t_hm *hm, t_pntr key, t_pntr value);
t_pntr						hm_lookup(t_hm *hm, t_pntr key);
int							hm_remove(t_hm *hash_map, t_pntr key);
size_t						hm_num_entries(t_hm *hash_map);

#endif
