/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:27:01 by cshinoha          #+#    #+#             */
/*   Updated: 2020/07/04 15:45:00 by cshinoha         ###   ########.ru       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/coreft.h"

void		ft_lstdel(t_node **alst, void (*del)(void *, size_t))
{
	t_node	*tmp;

	while (*alst)
	{
		tmp = (*alst)->next;
		del((*alst)->data, (*alst)->content_size);
		*alst = tmp;
		ft_memdel((void **)&tmp);
	}
}
