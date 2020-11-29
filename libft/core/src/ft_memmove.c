/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:33:04 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void				moveloop(const unsigned char *s,
		unsigned char *d,
		int vector,
		size_t n)
{
	while (n--)
	{
		*d = *s;
		s += vector;
		d += vector;
	}
}

void					*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	int					vector;

	if (!dst && !src)
		return (NULL);
	if (!n)
		return (dst);
	if (dst < src)
	{
		vector = 1;
		s = (unsigned char *)src;
		d = (unsigned char *)dst;
	}
	else
	{
		vector = -1;
		s = (unsigned char *)src + n - 1;
		d = (unsigned char *)dst + n - 1;
	}
	moveloop(s, d, vector, n);
	return (dst);
}
