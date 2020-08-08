/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:18 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 11:48:16 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <coreft.h>
# include <iterator.h>

typedef struct			s_linked_lst
{
	t_node				*first;
	t_node				*last;
	size_t				length;
}						t_lst;

t_lst					*lst_new();
void					lst_clear(t_lst *lst, f_free free_data);
void					lst_free(t_lst *lst, f_free free_data);
t_node					*lst_prepend(t_lst *lst, pointer data);
t_node					*lst_append(t_lst *lst, pointer data);
int						lst_contains(t_lst *lst, f_equal equal, pointer data);
void					lst_foreach(t_lst *lst, f_map merge_func);
void					lst_sort(t_lst *lst, f_compare compare_func);
t_node					*lst_nth_entry(t_lst *lst, size_t index);
pointer					lst_nth_data(t_lst *lst, size_t index);
pointer					*lst_to_array(t_lst *lst);
t_node					*lst_rm_entry(t_lst *lst, t_node *entry);
int						lst_rm_data(t_lst *lst, f_equal equal, pointer data);
t_itr					*lst_itr_load(t_lst *lst, t_itr *itr, f_prdct prdct);

#endif
