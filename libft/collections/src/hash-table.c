/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash-table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:29:37 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:59:44 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hash-table.h"

static int hm_allocate_table(t_hm *hash_map)
{
	hash_map->table_size = hash_map->prime_index < hm_num_primes ?
					 hm_primes[hash_map->prime_index] :
					 hash_map->entries * 10;
	return ((int)(hash_map->table =	ft_tmemalloc(sizeof(t_hm_entry *), hash_map->table_size)));
}

static void hm_free_entry(t_hm *hash_map, t_hm_entry *entry)
{
	if (hash_map->free_key)
		hash_map->free_key(entry->pair.key);
	if (hash_map->free_val)
		hash_map->free_val(entry->pair.value);
	free(entry);
}

t_hm *hm_new(f_hash hash_func, f_equal equal_func)
{
	t_hm *map;

	if (!(map = (t_hm *) malloc(sizeof(t_hm))))
		return (NULL);
	return (hm_init(map, hash_func, equal_func));
}

static int hm_enlarge(t_hm *hm)
{
	t_hm_entry **old_table;
	size_t old_table_size;
	t_hm_entry *next;
	size_t index;
	size_t i;

	old_table = hm->table;
	old_table_size = hm->table_size;
	hm->prime_index++;
	if (!hm_allocate_table(hm))
		return (0);
	i = 0;
	while (i < old_table_size)
	{
		while (old_table[i])
		{
			next = old_table[i]->next;
			index = hm->hash_func(old_table[i]->pair.key) % hm->table_size;
			old_table[i]->next = hm->table[index];
			hm->table[index] = old_table[i];
			old_table[i] = next;
		}
		i++;
	}
	free(old_table);
	return (1);
}

size_t hm_num_entries(t_hm *hash_map)
{
	return (hash_map->entries);
}

t_itr 					*hm_itr_load(t_hm *hash_map, t_itr *itr)
{
	size_t				chain;
	t_hm_entry 			*entry;
	t_node 				*new;
	t_node 				*tail;

	itr_clear(itr);
	chain = 0;
	while (chain < hash_map->table_size)
	{
		if (hash_map->table[chain])
		{
			entry = hash_map->table[chain];
			while (entry)
			{
				if (!(new = ft_lstnew(&entry->pair)))
					return (NULL);
				if (!itr->_cur_node) //TODO fix
					itr->_cur_node = new;
				else
				{
					new->prev = tail;
					tail->next = new;
				}
				tail = new;
				entry = entry->next;
			}
		}
		chain++;
	}
	itr->_start_node = itr->_cur_node;
	return (itr);
}

t_lst 					*hm_lst(t_hm *hash_map, f_prdct prdct)
{
	size_t				chain;
	t_hm_entry 			*entry;
	t_lst				*lst;

	chain = 0;
	if (!(lst = lst_new()))
		return (NULL);
	while (chain < hash_map->table_size)
	{
		if (hash_map->table[chain])
		{
			entry = hash_map->table[chain];
			while (entry)
			{
				if(!prdct || prdct(entry->pair.value))
					if (!(lst_prepend(lst, entry->pair.value)))
						return (NULL);
				entry = entry->next;
			}
		}
		chain++;
	}
	return (lst);
}



