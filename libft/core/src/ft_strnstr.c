/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:07:30 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/coreft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*stack;
	char	*ref;
	size_t	n_len;

	stack = (char *)haystack;
	ref = (char *)needle;
	n_len = ft_strlen(needle);
	if (!*needle)
		return (stack);
	while (*stack && len && len >= n_len)
	{
		if (ft_strstartwith(ref, stack))
			return (stack);
		stack++;
		len--;
	}
	return (NULL);
}
