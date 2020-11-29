/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_peek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:55:11 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_pntr			qu_peek_head(t_qu *qu)
{
	return (!qu_is_empty(qu) ? qu->head->data : NULL);
}

t_pntr			qu_peek_tail(t_qu *qu)
{
	if (qu_is_empty(qu))
		return (NULL);
	return (qu->tail->data);
}

int				qu_is_empty(t_qu *qu)
{
	return (!qu->head);
}
