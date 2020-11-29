/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:27:01 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

t_pntr		ft_node_del(t_node *node, void (*del)(void *))
{
	t_node	*tmp;

	if (node)
	{
		tmp = node->next;
		if (tmp)
			tmp->prev = node->prev;
		if (node->prev)
			node->prev->next = tmp;
		if (del)
			del(node->data);
	}
	return (node);
}
