/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stridexof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 22:24:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

long long		ft_strindexof(const char *s, int c)
{
	size_t		index;

	if (!s)
		return (-2);
	index = 0;
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		if (index + 1 < index)
			break ;
		index++;
	}
	if (s[index] == c)
		return (index);
	return (-1);
}
