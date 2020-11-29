/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 15:06:18 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../../core/includes/coreft.h"
# include "iterator.h"

typedef struct			s_linked_lst
{
	t_node				*first;
	t_node				*last;
	size_t				length;
}						t_lst;

t_lst					*lst_new();
void					lst_clear(t_lst *lst, t_ffree free_data);
void					lst_free(t_lst *lst, t_ffree free_data);
t_node					*lst_prepend(t_lst *lst, t_pntr data);
t_node					*lst_append(t_lst *lst, t_pntr data);
int						lst_contains(t_lst *lst, t_fequal equal, t_pntr data);
void					lst_foreach(t_lst *lst, t_fmap merge_func);
void					lst_sort(t_lst *lst, t_fcompare compare_func);
t_node					*lst_nth_entry(t_lst *lst, size_t index);
t_pntr					lst_nth_data(t_lst *lst, size_t index);
t_pntr					*lst_to_array(t_lst *lst);
t_node					*lst_rm_entry(t_lst *lst, t_node *entry);
int						lst_rm_data(t_lst *lst, t_fequal equal, t_pntr data);
t_itr					*lst_itr_load(t_lst *lst, t_itr *itr, t_fprdct prdct);

#endif
