/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:08:31 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include "../includes/coreft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	dlen;
	size_t	slen;
	size_t	index;

	dlen = 0;
	slen = 0;
	index = 0;
	while (src[slen])
		slen++;
	while (dst[dlen])
		dlen++;
	if (len <= dlen)
		return (ft_sizemin(dlen, len) + slen);
	dst += dlen;
	while (len - dlen - 1 > index && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (ft_sizemin(dlen, len) + slen);
}
