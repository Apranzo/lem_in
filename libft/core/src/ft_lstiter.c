/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:14:13 by cshinoha          #+#    #+#             */
/*   Updated: 2020/08/08 16:09:40 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/coreft.h"

void		ft_lstiter(t_node *lst, void (*f)(t_node *elem))
{
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
