/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_new_init_free_clear.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:55:10 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/07 14:59:44 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash-table.h"

static int hm_allocate_table(t_hm *hm)
{
	hm->table_size = hm->prime_index < hm_num_primes ?
					 hm_primes[hm->prime_index] :
					 hm->entries * 10;
	return ((int)(hm->table =
			ft_tmemalloc(sizeof(t_hm_entry *), hm->table_size)));
}

static void hm_free_entry(t_hm *hash_map, t_hm_entry *entry)
{
	if (hash_map->free_key)
		hash_map->free_key(entry->pair.key);
	if (hash_map->free_val)
		hash_map->free_val(entry->pair.value);
	free(entry);
}

t_hm *hm_init(t_hm *map, f_hash hash_func, f_equal equal_func)
{
	map->hash_func = hash_func;
	map->equal_func = equal_func;
	map->free_key = NULL;
	map->free_val = NULL;
	map->entries = 0;
	map->prime_index = 0;
	if (hm_allocate_table(map))
		return (map);
	free(map);
	return (NULL);
}

void			hm_clear(t_hm *hash_map)
{
	t_hm_entry *rover;
	t_hm_entry *next;
	size_t i;

	i = 0;
	while (i < hash_map->table_size)
	{
		rover = hash_map->table[i];
		while (rover != NULL)
		{
			next = rover->next;
			free(rover);
			rover = next;
		}
		i++;
	}
	free(hash_map->table);
}

void			hm_free(t_hm *hash_map, f_free free_key, f_free free_val)
{
	t_hm_entry *rover;
	t_hm_entry *next;
	size_t i;

	i = 0;
	if (free_key)
		hash_map->free_key = free_key;
	if (free_val)
		hash_map->free_val = free_val;
	while (i < hash_map->table_size)
	{
		rover = hash_map->table[i];
		while (rover)
		{
			next = rover->next;
			hm_free_entry(hash_map, rover);
			rover = next;
		}
		i++;
	}
	free(hash_map->table);
	free(hash_map);
}