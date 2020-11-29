/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_lookup_remove_insert.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:51:14 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

static t_hm_entry	*find_in_backet(t_hm_entry *rover,
		t_pntr key, t_fequal f_equal)
{
	while (rover && !f_equal(rover->pair.key, key))
		rover = rover->next;
	return (rover);
}

int					hm_insert(t_hm *hm, t_pntr key, t_pntr value)
{
	t_hm_entry		*entry;
	size_t			index;

	if ((hm->entries * 3) / hm->table_size > 0 &&
		!hm_enlarge(hm))
		return (0);
	index = hm->hash_func(key) % hm->table_size;
	entry = find_in_backet(hm->table[index], key, hm->equal_func);
	if (entry)
	{
		if (hm->free_val)
			hm->free_val(entry->pair.value);
		if (hm->free_key)
			hm->free_key(entry->pair.key);
	}
	else if (!(entry = (t_hm_entry *)malloc(sizeof(t_hm_entry))))
		return (0);
	else
		entry->next = hm->table[index];
	entry->pair.key = key;
	entry->pair.value = value;
	hm->table[index] = entry;
	hm->entries++;
	return (1);
}

t_pntr				hm_lookup(t_hm *hm, t_pntr key)
{
	t_hm_entry		*entry;
	size_t			index;

	if (!key)
		return (NULL);
	index = hm->hash_func(key) % hm->table_size;
	entry = find_in_backet(hm->table[index], key, hm->equal_func);
	return (entry ? (&(entry->pair))->value : NULL);
}

int					hm_remove(t_hm *hash_map, t_pntr key)
{
	t_hm_entry		**rover;
	t_hm_entry		*entry;
	t_pair			*pair;
	size_t			index;
	int				result;

	index = hash_map->hash_func(key) % hash_map->table_size;
	result = 0;
	rover = &hash_map->table[index];
	while (*rover)
	{
		pair = &((*rover)->pair);
		if (hash_map->equal_func(key, pair->key))
		{
			entry = *rover;
			*rover = entry->next;
			hm_free_entry(hash_map, entry);
			hash_map->entries--;
			result = 1;
			break ;
		}
		rover = &((*rover)->next);
	}
	return (result);
}
