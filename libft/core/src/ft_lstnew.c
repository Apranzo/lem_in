/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:03:14 by cshinoha          #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/coreft.h"
#include <stdlib.h>

t_node		*ft_lstnew(void const *data, size_t content_size)
{
	t_node	*new;
	void	*copy;

	copy = data && content_size ? malloc(content_size) : NULL;
	if (!(new = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	new->data = data ? ft_memcpy(copy, data, content_size) : NULL;
	new->content_size = data ? content_size : 0;
	new->next = NULL;
	return (new);
}
