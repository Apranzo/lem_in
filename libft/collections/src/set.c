#include "set.h"

#ifdef ALLOC_TESTING
#include "alloc-testing.h"
#endif

static const size_t set_primes[] = {
	193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
	196613, 393241, 786433, 1572869, 3145739, 6291469,
	12582917, 25165843, 50331653, 100663319, 201326611,
	402653189, 805306457, 1610612741,
};

static const size_t set_num_primes = sizeof(set_primes) / sizeof(int);

static int set_allocate_table(t_set *set)
{
	set->table_size = set->prime_index < set_num_primes ?
					  set_primes[set->prime_index] :
					  set->entries * 10;
	return ((int)(set->table =
					   ft_tmemalloc(sizeof(t_set_entry *), set->table_size)));

}

static void set_free_entry(t_set *set, t_set_entry *entry)
{
	if (set->free_func)
		set->free_func(entry->data);
	free(entry);
}

t_set 				*set_init(t_set *set, set_hash_f hash_func, set_equal_f equal_func)
{
	if (!(set = (t_set *) malloc(sizeof(t_set))))
		return (NULL);

	set->hash_func = hash_func;
	set->equal_func = equal_func;
	set->entries = 0;
	set->prime_index = 0;
	set->free_func = NULL;
	if (set_allocate_table(set))
		return (set);
	free(set);
	return (NULL);	
}

t_set *set_new(set_hash_f hash_func, set_equal_f equal_func)
{
	t_set *new_set;

	if (!(new_set = (t_set *) malloc(sizeof(t_set))))
		return (NULL);
	return (set_init(new_set, hash_func, equal_func));
}

void set_free(t_set *set)
{
	t_set_entry *rover;
	t_set_entry *next;
	size_t		i;

	i = 0;
	while (i < set->table_size)
	{
		rover = set->table[i];
		while (rover != NULL) {
			next = rover->next;
			set_free_entry(set, rover);
			rover = next;
		}
		i++;
	}
	free(set->table);
	free(set);
}

void set_register_free_function(t_set *set, set_free_val free_func)
{
	set->free_func = free_func;
}

static int set_enlarge(t_set *set)
{
	t_set_entry *next;
	t_set_entry **old_table;
	size_t old_table_size;
	size_t old_prime_index;
	size_t index;
	size_t i;

	/* Store the old table */

	old_table = set->table;
	old_table_size = set->table_size;
	old_prime_index = set->prime_index;
	set->prime_index++;

	if (!set_allocate_table(set))
	{
		set->table = old_table;
		set->table_size = old_table_size;
		set->prime_index = old_prime_index;
		return 0;
	}
	i = 0;
	while (i < old_table_size)
	{
		while (old_table[i])
		{
			next = old_table[i]->next;
			index = set->hash_func(old_table[i]->data) % set->table_size;
			old_table[i]->next = set->table[index];
			set->table[index] = old_table[i];
			old_table[i] = next;
		}
		i++;
	}
	free(old_table);
	return (1);
}

int set_insert(t_set *set, set_val data)
{
	t_set_entry *newentry;
	t_set_entry *rover;
	size_t index;

	if ((set->entries * 3) / set->table_size > 0 &&
		!set_enlarge(set))
		return (0);
	index = set->hash_func(data) % set->table_size;
	rover = set->table[index];
	while (rover)
	{
		if (set->equal_func(data, rover->data))
			return (0);
		rover = rover->next;
	}
	if (!(newentry = (t_set_entry *) malloc(sizeof(t_set_entry))))
		return (0);
	newentry->data = data;
	newentry->next = set->table[index];
	set->table[index] = newentry;
	set->entries++;
	return (1);
}

int set_remove(t_set *set, set_val data)
{
	t_set_entry **rover;
	t_set_entry *entry;
	size_t index;

	index = set->hash_func(data) % set->table_size;
	rover = &set->table[index];
	while (*rover)
	{
		if (set->equal_func(data, (*rover)->data)) {
			entry = *rover;
			*rover = entry->next;
			set->entries--;
			set_free_entry(set, entry);
			return (1);
		}
		rover = &((*rover)->next);
	}
	return (0);
}

int set_query(t_set *set, set_val data)
{
	t_set_entry *rover;
	size_t index;

	index = set->hash_func(data) % set->table_size;
	rover = set->table[index];
	while (rover)
	{
		if (set->equal_func(data, rover->data))
			return (1);
		rover = rover->next;
	}
	return (0);
}

size_t set_num_entries(t_set *set)
{
	return set->entries;
}

set_val *set_to_array(t_set *set)
{
	set_val *array;
	int array_counter;
	size_t i;
	t_set_entry *rover;

	/* Create an array to hold the set entries */

	array = malloc(sizeof(set_val) * set->entries);

	if (array == NULL) {
		return NULL;
	}

	array_counter = 0;

	/* Iterate over all entries in all chains */

	for (i=0; i<set->table_size; ++i) {

		rover = set->table[i];

		while (rover != NULL) {

			/* Add this value to the array */

			array[array_counter] = rover->data;
			++array_counter;

			/* Advance to the next entry */

			rover = rover->next;
		}
	}

	return array;
}

t_set *set_union(t_set *set1, t_set *set2)
{
	t_set_iter iterator;
	t_set *new_set;
	set_val value;

	new_set = set_new(set1->hash_func, set1->equal_func);

	if (new_set == NULL) {
		return NULL;
	}

	/* Add all values from the first set */

	set_iterate(set1, &iterator);

	while (set_iter_has_more(&iterator)) {

		/* Read the next value */

		value = set_iter_next(&iterator);

		/* Copy the value into the new set */

		if (!set_insert(new_set, value)) {

			/* Failed to insert */

			set_free(new_set);
			return NULL;
		}
	}

	/* Add all values from the second set */

	set_iterate(set2, &iterator);

	while (set_iter_has_more(&iterator)) {

		/* Read the next value */

		value = set_iter_next(&iterator);

		/* Has this value been put into the new set already?
		 * If so, do not insert this again */

		if (set_query(new_set, value) == 0) {
			if (!set_insert(new_set, value)) {

				/* Failed to insert */

				set_free(new_set);
				return NULL;
			}
		}
	}

	return new_set;
}

t_set *set_intersection(t_set *set1, t_set *set2)
{
	t_set *new_set;
	t_set_iter iterator;
	set_val value;

	new_set = set_new(set1->hash_func, set2->equal_func);

	if (new_set == NULL) {
		return NULL;
	}

	/* Iterate over all values in set 1. */

	set_iterate(set1, &iterator);

	while (set_iter_has_more(&iterator)) {

		/* Get the next value */

		value = set_iter_next(&iterator);

		/* Is this value in set 2 as well?  If so, it should be
		 * in the new set. */

		if (set_query(set2, value) != 0) {

			/* Copy the value first before inserting,
			 * if necessary */

			if (!set_insert(new_set, value)) {
				set_free(new_set);

				return NULL;
			}
		}
	}

	return new_set;
}

void set_iterate(t_set *set, t_set_iter *iter)
{
	size_t chain;

	iter->set = set;
	iter->next_entry = NULL;
	chain = 0;
	while (chain < set->table_size)
	{
		if (!set->table[chain] && ++chain)
			continue ;
		iter->next_entry = set->table[chain];
		chain++;
	}

	iter->next_chain = chain;
}

set_val set_iter_next(t_set_iter *iterator)
{
	t_set *set;
	set_val result;
	t_set_entry *current_entry;
	size_t chain;

	set = iterator->set;

	/* No more entries? */

	if (!iterator->next_entry) {
		return NULL;
	}

	/* We have the result immediately */

	current_entry = iterator->next_entry;
	result = current_entry->data;

	/* Advance next_entry to the next SetEntry in the Set. */

	if (current_entry->next) {

		/* Use the next value in this chain */

		iterator->next_entry = current_entry->next;

	} else {

		/* Default value if no valid chain is found */

		iterator->next_entry = NULL;

		/* No more entries in this chain.  Search the next chain */

		chain = iterator->next_chain + 1;

		while (chain < set->table_size) {

			/* Is there a chain at this table entry? */

			if (set->table[chain]) {

				/* Valid chain found! */

				iterator->next_entry = set->table[chain];

				break;
			}

			/* Keep searching until we find an empty chain */

			++chain;
		}

		iterator->next_chain = chain;
	}

	return result;
}

int set_iter_has_more(t_set_iter *iterator)
{
	return (iterator->next_entry != NULL);
}

