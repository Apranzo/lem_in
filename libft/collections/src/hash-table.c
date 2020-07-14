#include "../includes/hash-table.h"

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

static const size_t hm_primes[] = {
	193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
	196613, 393241, 786433, 1572869, 3145739, 6291469,
	12582917, 25165843, 50331653, 100663319, 201326611,
	402653189, 805306457, 1610612741,
};

static const size_t hm_num_primes = sizeof(hm_primes) / sizeof(size_t);


static int hm_allocate_table(t_hash_map *hash_map)
{
	hash_map->table_size = hash_map->prime_index < hm_num_primes ?
					 hm_primes[hash_map->prime_index] :
					 hash_map->entries * 10;
	return (!!(hash_map->table =
				ft_tmemalloc(sizeof(t_hm_entry *), hash_map->table_size)));
}

static void hm_free_entry(t_hash_map *hash_map, t_hm_entry *entry)
{
	if (hash_map->free_key)
		hash_map->free_key(entry->pair.key);
	if (hash_map->free_val)
		hash_map->free_val(entry->pair.value);
	free(entry);
}

t_hash_map *hm_init(t_hash_map *map, hm_hash_f hash_func, hm_equal_f equal_func)
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

t_hash_map *hm_new(hm_hash_f hash_func, hm_equal_f equal_func)
{
	t_hash_map *map;

	if (!(map = (t_hash_map *) malloc(sizeof(t_hash_map))))
		return (NULL);
	return (hm_init(map, hash_func, equal_func));
}

void			hm_clear(t_hash_map *hash_map)
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

void			hm_free(t_hash_map *hash_map)
{
	t_hm_entry *rover;
	t_hm_entry *next;
	size_t i;

	i = 0;
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

void hm_register_free_functions(t_hash_map *hash_map,
										hm_free_key key_free_func,
										hm_free_val value_free_func)
{
	hash_map->free_key = key_free_func;
	hash_map->free_val = value_free_func;
}

static int hm_enlarge(t_hash_map *hash_map)
{
	t_hm_entry **old_table;
	size_t old_table_size;
	size_t old_prime_index;
	t_hm_entry *next;
	size_t index;
	size_t i;

	old_table = hash_map->table;
	old_table_size = hash_map->table_size;
	old_prime_index = hash_map->prime_index;
	hash_map->prime_index++;
	if (!hm_allocate_table(hash_map))
	{
		hash_map->table = old_table;
		hash_map->table_size = old_table_size;
		hash_map->prime_index = old_prime_index;
		return (0);
	}
	i = 0;
	while (i < old_table_size)  //TODO CHECK iT
	{
		while (old_table[i])
		{
			next = old_table[i]->next;
			index = hash_map->hash_func(old_table[i]->pair.key) % hash_map->table_size;
			old_table[i]->next = hash_map->table[index];
			hash_map->table[index] = old_table[i];
			old_table[i] = next;
		}
		i++;
	}
	free(old_table);
	return (1);
}

int hm_insert(t_hash_map *hash_map, pointer key,
					pointer value)
{
	t_hm_entry *rover;
	t_pair *pair;
	t_hm_entry *newentry;
	size_t index;

	/* If there are too many items in the table with respect to the table
	 * size, the number of hash collisions increases and performance
	 * decreases. Enlarge the table size to prevent this happening */

	if ((hash_map->entries * 3) / hash_map->table_size > 0 &&
		!hm_enlarge(hash_map))
		return (0);
	/* Generate the hash of the key and hence the index into the table */
	index = hash_map->hash_func(key) % hash_map->table_size;
	/* Traverse the chain at this location and look for an existing
	 * entry with the same key */
	rover = hash_map->table[index];
	while (rover)
	{
		/* Fetch rover's HashTablePair entry */
		pair = &(rover->pair);
		if (hash_map->equal_func(pair->key, key)) {
			/* Same key: overwrite this entry with new data */
			/* If there is a pointer free function, free the old data
			 * before adding in the new data */
			if (hash_map->free_val)
				hash_map->free_val(pair->value);
			/* Same with the key: use the new key pointer and free
			 * the old one */
			if (hash_map->free_key)
				hash_map->free_key(pair->key);
			pair->key = key;
			pair->value = value;
			/* Finished */
			return (1);
		}
		rover = rover->next;
	}
	/* Not in the hash table yet.  Create a new entry */
	if (!(newentry = (t_hm_entry *) malloc(sizeof(t_hm_entry))))
		return (0);
	newentry->pair.key = key;
	newentry->pair.value = value;
	/* Link into the list */
	newentry->next = hash_map->table[index];
	hash_map->table[index] = newentry;
	/* Maintain the count of the number of entries */
	hash_map->entries++;
	/* Added successfully */
	return (1);
}

pointer hm_lookup(t_hash_map *hash_map, pointer key)
{
	t_hm_entry *rover;
	t_pair *pair;
	size_t index;

	/* Generate the hash of the key and hence the index into the table */
	index = hash_map->hash_func(key) % hash_map->table_size;
	/* Walk the chain at this index until the corresponding entry is
	 * found */
	rover = hash_map->table[index];
	while (rover)
	{
		pair = &(rover->pair);
		if (hash_map->equal_func(key, pair->key))
			/* Found the entry.  Return the data. */
			return (pair->value);
		rover = rover->next;
	}
	/* Not found */
	return (NULL);
}

int hm_remove(t_hash_map *hash_map, pointer key)
{
	t_hm_entry **rover;
	t_hm_entry *entry;
	t_pair *pair;
	size_t index;
	int result;

	/* Generate the hash of the key and hence the index into the table */
	index = hash_map->hash_func(key) % hash_map->table_size;
	/* Rover points at the pointer which points at the current entry
	 * in the chain being inspected.  ie. the entry in the table, or
	 * the "next" pointer of the previous entry in the chain.  This
	 * allows us to unlink the entry when we find it. */
	result = 0;
	rover = &hash_map->table[index];
	while (*rover)
	{
		pair = &((*rover)->pair);
		if (hash_map->equal_func(key, pair->key))
		{
			/* This is the entry to remove */
			entry = *rover;
			/* Unlink from the list */
			*rover = entry->next;
			/* Destroy the entry structure */
			hm_free_entry(hash_map, entry);
			/* Track count of entries */
			hash_map->entries--;
			result = 1;
			break ;
		}
		/* Advance to the next entry */
		rover = &((*rover)->next);
	}
	return (result);
}

size_t hm_num_entries(t_hash_map *hash_map)
{
	return (hash_map->entries);
}

t_itr 					*hm_itr_load(t_hash_map *hash_map, t_itr *itr)
{
	size_t				chain;
	t_hm_entry 			*entry;
	t_node 				*new;
	t_node 				*tail;

	/* Default pointer of next if no entries are found. */
	itr_clear(itr);
	itr->collection = hash_map;
	/* Find the first entry */
	chain = 0;
	tail = itr->_cur_node;
	while (chain < hash_map->table_size)
	{
		if (hash_map->table[chain])
		{
			entry = hash_map->table[chain];
			while (entry)
			{
				if (!(new = ft_memalloc(sizeof(t_node))))
					return (NULL);
				new->data = &entry->pair;
				if (!itr->_cur_node) //TODO fix
				{
					itr->_cur_node = new;
					new->prev = itr->_cur_node;
				}
				else
				{
					new->prev = tail;
					tail->next = new;
				}
				tail = new;
				entry = entry->next;
			}
//			itr->next_chain = chain;
			break ;
		}
		chain++;
	}
	return (itr);
}



