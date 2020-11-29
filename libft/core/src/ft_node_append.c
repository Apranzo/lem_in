/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:29:22 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

t_node		*ft_node_append(t_node **node, t_pntr data)
{
	t_node	*rover;
	t_node	*new;

	if (!node || !(new = ft_lstnew(data)))
		return (NULL);
	if (*node)
	{
		rover = *node;
		while (rover->next)
			rover = rover->next;
		new->prev = rover;
		rover->next = new;
	}
	*node = new;
	return (new);
}
