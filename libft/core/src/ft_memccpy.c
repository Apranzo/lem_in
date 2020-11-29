/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:37:40 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void					*ft_memccpy(void *dst,
									const void *src, int c, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	unsigned char		stop_word;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	stop_word = (unsigned char)c;
	while (n--)
	{
		*(d++) = *s;
		if (*s == stop_word)
			return (d);
		s++;
	}
	return (NULL);
}
