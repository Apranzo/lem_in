/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:36:39 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/15 18:45:19 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void				*ft_clear(void *start, size_t len)
{
	unsigned char	*area;

	if (!start)
		return (NULL);
	area = (unsigned char*)start;
	while (len--)
		*(area++) = '\0';
	return (start);
}
