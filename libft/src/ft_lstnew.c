/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:03:14 by cshinoha          #+#    #+#             */
/*   Updated: 2019/05/26 20:05:47 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*copy;

	copy = content && content_size ? malloc(content_size) : NULL;
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content = content ? ft_memcpy(copy, content, content_size) : NULL;
	new->content_size = content ? content_size : 0;
	new->next = NULL;
	return (new);
}
