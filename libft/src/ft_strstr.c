/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:51:18 by cshinoha          #+#    #+#             */
/*   Updated: 2019/04/27 16:18:48 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../include/libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	char	*stack;
	char	*ref;

	stack = (char *)haystack;
	ref = (char *)needle;
	if (!*needle)
		return (stack);
	while (*stack)
	{
		if (ft_strstartwith(ref, stack))
			return (stack);
		stack++;
	}
	return (NULL);
}
