/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 23:16:49 by cshinoha          #+#    #+#             */
/*   Updated: 2019/05/26 20:02:53 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstpush(t_list **begin_list, void *content, size_t content_size)
{
	t_list *first;

	first = ft_lstnew(content, content_size);
	first->next = *begin_list;
	if (*begin_list)
		(*begin_list)->prev = first;
	first->prev = NULL;
	*begin_list = first;
	return (*begin_list);
}
