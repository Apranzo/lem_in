/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:21:58 by cshinoha          #+#    #+#             */
/*   Updated: 2019/05/08 23:00:48 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_count_if(void **tab, int (*f)(void *))
{
	size_t counter;

	counter = 0;
	while (*tab)
	{
		if (f(*tab))
			counter++;
		tab++;
	}
	return (counter);
}
