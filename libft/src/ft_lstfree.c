/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:01:16 by cshinoha          #+#    #+#             */
/*   Updated: 2020/02/27 14:28:45 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void		ft_lstfree(t_list *node, size_t len)
{
	t_list	*tmp;

	if (!len)
		len--;
	while (node && len--)
	{
		tmp = node->next;
		free(node->content);
		free(node);
		node = tmp;
	}
}
