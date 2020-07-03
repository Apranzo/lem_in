/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 20:18:27 by cshinoha          #+#    #+#             */
/*   Updated: 2020/03/14 15:00:25 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void				*ft_memset(void *d, int c, size_t len)
{
	unsigned char	*t;

	t = (unsigned char *)d;
	while (len--)
		*(t++) = (unsigned char)c;
	return (d);
}
