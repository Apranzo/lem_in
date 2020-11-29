/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_new_init_free_clear.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:55:10 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

static int		hm_allocate_table(t_hm *hash_map)
{
	hash_map->table_size = hash_map->prime_index < g_hm_num_primes
							? g_hm_primes[hash_map->prime_index]
							: hash_map->entries * 10;
	return ((int)(hash_map->table =
			ft_tmemalloc(sizeof(t_hm_entry *), hash_map->table_size)));
}

void			hm_free_entry(t_hm *hash_map, t_hm_entry *entry)
{
	if (hash_map->free_key)
		hash_map->free_key(entry->pair.key);
	if (hash_map->free_val)
		hash_map->free_val(entry->pair.value);
	free(entry);
}

t_hm			*hm_init(t_hm *map, t_fhash hash_func, t_fequal equal_func)
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

t_hm			*hm_clear(t_hm *hash_map)
{
	t_hm_entry	*rover;
	t_hm_entry	*next;
	size_t		i;

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
	if (hm_allocate_table(hash_map))
		return (hash_map);
	return (NULL);
}

void			hm_free(t_hm *hash_map, t_ffree free_key, t_ffree free_val)
{
	t_hm_entry	*rover;
	t_hm_entry	*next;
	size_t		i;

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
