/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 23:39:59 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"

t_node		*ft_lstmap(t_node *lst, t_node *(*f)(t_node *elem))
{
	t_node	*first;
	t_node	*new;

	new = f(lst);
	first = new;
	lst = lst->next;
	while (lst)
	{
		new->next = f(lst);
		lst = lst->next;
		new = new->next;
	}
	return (first);
}
