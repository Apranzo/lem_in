/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:03:14 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 16:09:40 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <coreft.h>

t_node		*ft_lstnew(void *data)
{
	t_node	*new;

	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
