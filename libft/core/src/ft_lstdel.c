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

void		ft_lstdel(t_node **alst, void (*del)(void *))
{
	t_node	*tmp;

	while (alst && *alst)
	{
		tmp = (*alst)->next;
		if (tmp && (tmp->prev = (*alst)->prev))
			tmp->prev->next = tmp;
		if (del)
			del((*alst)->data);
		*alst = tmp;
	}
}
