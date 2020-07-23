#ifndef lst_H
# define lst_H

#include <coreft.h>
#include <iterator.h>

typedef struct s_linked_lst
{
	t_node				*first;
	t_node				*last;
	size_t				length;	
}						t_lst;

t_lst					*lst_new();

void lst_free(t_lst *lst);
t_node *lst_prepend(t_lst *lst, pointer data);
t_node *lst_append(t_lst *lst, pointer data);

/**
 * Retrieve the previous entry in a lst.
 *
 * @param t_node    Pointer to the lst entry.
 * @return             The previous entry in the lst, or NULL if this
 *                     was the first entry in the lst.
 */

//t_node *lst_prev(t_node *t_node);

/**
 * Retrieve the next entry in a lst.
 *
 * @param t_node    Pointer to the lst entry.
 * @return             The next entry in the lst, or NULL if this was the
 *                     last entry in the lst.
 */

//t_node *lst_next(t_node *t_node);

/**
 * Retrieve the value at a lst entry.
 *
 * @param t_node    Pointer to the lst entry.
 * @return             The value stored at the lst entry.
 */

//pointer lst_data(t_node *t_node);

/**
 * Set the value at a lst entry. The value provided will be written to the 
 * given t_node. If t_node is NULL nothing is done.
 *
 * @param t_node 	Pointer to the lst entry.
 * @param value			The value to set.
 */
//void lst_set_data(t_node *t_node, pointer value);

/**
 * Retrieve the entry at a specified index in a lst.
 *
 * @param lst       The lst.
 * @param index     The index into the lst .
 * @return          The entry at the specified index, or NULL if out of range.
 */
void					lst_sort(t_lst *lst, f_compare compare_func);
t_node 					*lst_nth_entry(t_lst *lst, size_t index);
pointer					lst_nth_data(t_lst *lst, size_t index);
pointer					*lst_to_array(t_lst *lst);
int						lst_remove_entry(t_lst *lst, t_node *entry);
t_itr					*lst_itr_load(t_lst *lst, t_itr *itr, f_prdct prdct);

#endif

